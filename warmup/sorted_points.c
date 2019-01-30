#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "point.h"
#include "sorted_points.h"
#include <math.h>
#include <stdbool.h>

/* this structure should store all the points in a list in sorted order. */
struct sorted_points {
	/* you can define this struct to have whatever fields you want. */
	double x;
	double y;
	double d; 	//d=distance
	struct sorted_points *next;
};
typedef struct sorted_points sorted_points;

/* think about where you are going to store a pointer to the next element of the
 * linked list? if needed, you may define other structures. */

struct sorted_points 
*sp_init()
{
	struct sorted_points *sp;

	sp = (struct sorted_points *)malloc(sizeof(struct sorted_points));
	assert(sp);

	//First node is junk
	sp->x = 0;
	sp->y = 0;
	sp->d = 0;
	sp->next = NULL;

	return sp;
}

bool
node_of_insertion(struct sorted_points *current, struct sorted_points *new_point)
{
	if(current->next->d > new_point->d)
		return true;
	else if (current->next->d == new_point->d) 
	{
		if (current->next->x > new_point->x)
			return true;
		else if (current->next->x == new_point->x && current->next->y >= new_point->y)
					return true;
	}
	return false;
}

void
sp_destroy(struct sorted_points *sp)
{
	while(sp!=NULL)
	{
		sorted_points *current = sp;		
		sp=sp->next;
		free(current);
	}
}

int
sp_add_point(struct sorted_points *sp, double x, double y)
{	
	//Allocate new point to be added	
	sorted_points *new_point = sp_init();
	new_point->x = x;
	new_point->y = y;
	new_point->d = sqrt(pow(x,2)+pow(y,2));
	new_point->next = NULL;

	//if empty list
	if(sp->next==NULL)
	{
		sp->next = new_point;
		return 1;
	}
	//if not empty list
	else
	{
		//Initialize current
		sorted_points * current = sp;
		//Traverse Nodes until find node of insertion or end
		while(current->next!=NULL)
		{
			//if found point of insertion, insert node
			if(node_of_insertion(current, new_point))
			{
				new_point->next = current->next;
				current->next = new_point;
				return 1;
			}
			//else traverse to next node
			current=current->next;
		}
		//Reached end of linkedlist, insert new point
		current->next= new_point;
		return 1;
	}
	
	//Prevent memory leak
	free(new_point);
	return 0;
}

int
sp_remove_first(struct sorted_points *sp, struct point *ret)
{
	if(sp->next==NULL)
		return 0;
	else
	{
		sorted_points * delete_point = sp->next;
		sp->next = delete_point->next;
		ret = point_set(ret,delete_point->x,delete_point->y);
		free(delete_point);
		return 1;
	}
}

int
sp_remove_last(struct sorted_points *sp, struct point *ret)
{
	if(sp->next==NULL)
		return 0;
	else
	{
		sorted_points *current = sp->next;
		sorted_points *previous = sp;
		//traverse until second last node
		while(current->next!=NULL)
		{
			previous = current;
			current = current-> next;
		}
		ret = point_set(ret,current->x,current->y);
		previous->next = NULL;
		free(current);
		return 1;
	}
}

int
sp_remove_by_index(struct sorted_points *sp, int index, struct point *ret)
{
	//if index is negative or empty list, failure
	if (index<0 || sp->next==NULL)
		return 0;
	else 
	{
		sorted_points *current = sp->next;
		sorted_points *previous = sp;
		for(;index!=0;index--)
		{
			//return 0 if index is greater than size of linkedlist
			if(current->next== NULL)
				return 0;
			//traverse until index
			previous = current;
			current = current->next;
		}
		//if at end of linkedlist
		if (current->next==NULL)
		{
			previous->next=NULL;
			
		}
		else
		{
			previous->next=current->next;
		}
		ret = point_set(ret,current->x,current->y);
		free(current);
		return 1;
	}
}

int
sp_delete_duplicates(struct sorted_points *sp)
{
	//if empty list, return 0
	if (sp->next==NULL)
		return 0;
	else
	{
		int count = 0;
		sorted_points *current = sp->next;
		sorted_points *previous = sp;
		while(current!= NULL)
		{
			if (current->x == previous->x && current->y == previous->y)
			{
				previous->next = current->next;
				free(current);				
				current = previous->next;
				count++;
			}
			else
			{
				previous = current;		
				current = current->next;
			}
		}
		return count;
	}
		return -1;
}
