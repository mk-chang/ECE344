#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int factorial(int n){
	if (n>=1)
		return n*factorial(n-1);
	else 
		return 1;
}

bool is_integar(char* input)
{
	//0 in ascii is 48,9 in ascii is 57
	int i=0;
	while(input[i] != '\0')
	{
		if(input[i]<48 || input[i]>57)
			return false;
		i++;
	}
	return true;
}

int
main(int argc,char* argv[])
{
	if(argc==2 && is_integar(argv[1]))
	{
		int n = atoi(argv[1]);
		if (n<=0)
			printf("Huh?\n");
		else if (n>12)
			printf("Overflow\n");
		else
		{
			int result = factorial(n);
			printf("%d\n",result);
		}
	}
	else
		printf("Huh?\n");
	return 0;
}
