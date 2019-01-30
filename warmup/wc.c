#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "wc.h"

#include <string.h> // because we use strcmp
#include <ctype.h> // because we use isspace

//LinkedList in hash table
typedef struct element{
	int count;
	char *word;
	struct element *next;
}node;

struct wc{
	node **hash_table;
	long table_size;
};

//hash function from www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str, long table_size) //Consider changing to unsigned long 
{
  int hash = 5381;
  int c = 0;

  while ((c = *str++)!=0)
  {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }

  if(hash<0)
     hash *= -1;

  hash = hash%table_size;

  return hash;
}

//Adds word to hash table
int word_to_table(struct wc *wc, char *word, long key)
{
	//For first entry
	if(wc->hash_table[key] == NULL)
	{
		wc->hash_table[key] = (node *)malloc(sizeof(node));
		wc->hash_table[key]->count =1;
		wc->hash_table[key]->word = word;
		wc->hash_table[key]->next = NULL;
		return 1;
	}
	//Checking for collision
	node *current= wc->hash_table[key];
	node *previous = NULL;
	
	//Go through linkedlist until find matching word or hit end
	while(current!=NULL)
	{
		//Check if word exists
		if(strcmp(word,current->word)==0)
		{
			current->count++;
			free(word);
			return 1;
		}
		previous = current;
		current = current->next;
	}
	//Reached end of table and did not find, therefore add to end of linkedlist
	previous->next = (node *)malloc(sizeof(node));
	previous->next->count =1;
	previous->next->word = word;
	previous->next->next = NULL;
	return 1;
}

struct wc *
wc_init(char *word_array, long size)
{
	struct wc *wc;

	wc = (struct wc *)malloc(sizeof(struct wc));
	assert(wc);

	wc->hash_table = (node **)malloc(size * sizeof(node*));
	assert(wc->hash_table);
	wc->table_size = size/4; // size argument stored in table_size of wc structure.
	
	char *current_word=NULL; //initialize pointer to current word that I want to store in hash table
	long key;
	int last_word=0; //last word index in word_array
	int word_length=0; //length of current word
	int i; //index of word array
	int j = 0; //index of current word

	for (i = 0; word_array[i] != '\0'; i++){ 
		if (isspace(word_array[i])) // if the character is space
		{
			// make sure this is not the beginning of the word, and is the last. (ie. double spaces)
			if (word_length != 0) 
			{ 
				//allocate string with null character at end
				current_word = (char *)malloc((word_length+1)*sizeof(char));
				assert(current_word);
				
				//Create temporary word
				for (j=0; j < word_length; j++)
				{ 
					current_word[j] = word_array[last_word+j];
				}
				// add the null at the end of word
				current_word[j] = '\0'; 
				assert(current_word);
				
				//calculate hash key
				key = hash(current_word, wc->table_size);

				//add word to table
				word_to_table(wc,current_word,key);
			}
			//reset j,wordlength and update last_word index for next word
			last_word = i+1;
			word_length = 0;
		}
		else 
			word_length ++;
	}
	return wc;
}

//print the linkedlist in hash entry
void print_linkedlist(node *linkedlist)
{
	node *current = linkedlist;
	while(current!=NULL)
	{
		printf("%s:%d\n",current->word,current->count);
		current = current->next;
	}
}

void
wc_output(struct wc *wc)
{
	for(long i=0;i<wc->table_size;i++)
	{
		if(wc->hash_table[i]!=NULL)
			print_linkedlist(wc->hash_table[i]);
	}
}

//delete the entry in hash table
void hash_entry_delete(node *linkedlist)
{
	while(linkedlist!=NULL)
	{
		node *temp = linkedlist;
		linkedlist = linkedlist->next;
		free(temp);
	}
}

void
wc_destroy(struct wc *wc)
{
	for(long i=0;i<wc->table_size;i++)
	{
		if(wc->hash_table[i]!=NULL)
			hash_entry_delete(wc->hash_table[i]);
	}
	free(wc);
}
