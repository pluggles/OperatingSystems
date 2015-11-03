/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 3 - Problem 1
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 10/09/15
*************************************************/
#define _POSIX_C_SOURCE 199309L  /*seems like i need this timespec*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


int getArraySize (int, char **);
/* global varible */
int ARRAYSIZE;
/********************************************
* keeps track of time
* gets size of array
* populates array
*******************************************/
int main(int argc, char *argv[]) {
	struct timespec start, finish;
	double elapsed;
	int i;
	clock_gettime(CLOCK_MONOTONIC, & start);
	
	if (getArraySize(argc, argv) == -1) { /*get the array size from command line */
		return -1;
	}
	srand(time(NULL));
	int *array;
	array = malloc (sizeof(int) * ARRAYSIZE);
	for (i = 0; i < ARRAYSIZE; i++) {
		array[i] =rand();
		/* print to check random numbers are random */
		/*printf("array index %d has value: %d\n", i, array[i]); */
	}

	free(array);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Elapsed time for array of size %i  Sequential Code: %f\n", ARRAYSIZE, elapsed);
	return 0;
}
/********************************************
* gets the argument from the command line to
* find the size of the array
* ARRAYSIZE is a global varible
*********************************************/
int getArraySize (int argc, char *argv[]) {
	
	char badChar;
	/* checks if proper number of args */
	if (argc != 2) {
		printf("Error ussage is: %s [Number]\n", argv[0]); 
		return -1;
	/* checks if number was entered */
	} else if (sscanf (argv[1], "%i %c", &ARRAYSIZE, &badChar)!=1) { 
		printf("Please enter a valid integer not: %s\n", argv[1]);
		return -1;
	/* checks if positive number */
	} else if (ARRAYSIZE <= 0) { 
		printf("Please enter a valid positive integer\n");
		return -1;
	} else {
		return 0;
	}

}
