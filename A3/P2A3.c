/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 3 - Problem 2
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 10/09/15
*************************************************/

/*Threading problem */
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>



int getArraySize (int, char **);
void * populateArray(void *);

int ARRAYSIZE;
int *array;

/*number of threads */
#define P 4
/***************************************
* gets size of array from command line
* mallocs size for array
* creates threads
* keeps track of time
*****************************************/
int main(int argc, char *argv[]) {
	struct timespec start, finish; /* time delcaration stuff given by Lilien*/
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, & start); /* get start time */
	int i;
	if (getArraySize(argc, argv) == -1) { /*get the array size from command line */
		return -1;
	}
	/* malloc mem for large array */
	array = malloc (sizeof(int) * ARRAYSIZE);
	
	pthread_t threads[P]; /*create thread datatypes */
	for(i = 0; i < P; ++i) {
		int *arg = malloc(sizeof(*arg)); /*get threadID */
		*arg = i;
		/*call thread method, passing id */
		if(pthread_create(&threads[i], NULL, populateArray, arg)) { 
			perror("pthread create: ");
			exit(1);
		}
	}
	/*return val used for joining */
	void *retVal;
	for(i=0; i < P; ++i) {
		/* join the threads back */
		pthread_join(threads[i], &retVal);
	}
	/* following bit commented out, used to test if array is made correctly 
	for (i = 0; i < ARRAYSIZE; i++) {
		array[i] =rand();
		print to check random numbers are random 
		printf("array index %d has value: %d\n", i, array[i]); 
	}*/
	free(array);
	clock_gettime(CLOCK_MONOTONIC, &finish); /*get end time */
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Elapsed time for array of size %i using Parallel Code: %f\n", ARRAYSIZE, elapsed);
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
		printf("Please enter a valid integer\n");
		return -1;
	/* checks if positive number */
	} else if (ARRAYSIZE <= 0) { 
		printf("Please enter a valid positive integer\n");
		return -1;
	} else {
		return 0;
	}

}
/********************************************
* Threading method
* gets the thread count (x), uses that to figure out
* what pirtion of the array to populate
*******************************************/
void * populateArray(void *x) {
	int thread = *((int*) x); /* gets the thread id */
	free(x);
	/* get quarter size of array */
	double base = floor((double)(ARRAYSIZE/4));
	int start, end; //index
	/* each case populates the correct spot of array */
	switch (thread) {
		case 0: /* first quarter filled with 0 */
			start = 0;
			end = (int)floor(ARRAYSIZE/4);
			for (start=start; start <= end; start++) {
				array[start] = 0;
			}
			break;
		case 1: /* second quarter filled with 1 */
			start = (int)floor(ARRAYSIZE/4) + 1;
			end = (int)floor(ARRAYSIZE/2);
			for (start=start; start <= end; start++) {
				array[start] = 1;
			}
			break;
		case 2: /* third quarter filled with 2 */
			start = (int)floor(ARRAYSIZE/2) + 1;
			end = base*3;
			for (start=start; start <= end; start++) {
				array[start] = 2;
			}
			break;
		case 3: /* fourth quarter filled with 3 */
			start = base*3 + 1;
			end = ARRAYSIZE-1;
			for (start=start; start <= end; start++) {
				array[start] = 3;
			}
			break;
		default:
			printf("something is wrong\n");

	}

	pthread_exit(0);
}