/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 1 - Problem 2
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 09/21/15
*************************************************/


#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int main()
{
	time_t t;
	srand((unsigned) time(&t));	//gen a random seed
	int numbers[MAXSIZE];
	char letters[MAXSIZE];

	int i, n;
	char c;

	for (i=0; i < MAXSIZE; i++){  //populate numbers array
		n = rand() % 1000 + 1;  //make sure in range
		numbers[i] = n;
		if (i%2 == 0 && i > 1){
			printf("%d, ", numbers[i]); //print even index values
		}
	}
	printf("\n");
	for (i=0; i <MAXSIZE; i++){  //populate numbers array
		c = 'A' + rand() % 26;  //make sure in range
		letters[i] = c;
		if (i%2 == 0 && i > 1){
			printf("%c, ", letters[i]); //print even index values
		}
	}
	printf("\n");
}