/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 3 - Problem 2
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 10/09/15
*************************************************/

/*Threading problem */
#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>
#include <unistd.h>
#include <math.h>



int getArraySize (int, char **);
void * populateArray(void *);

int ARRAYSIZE;
int *array;

/*number of processes */
#define P 4

int main(int argc, char *argv[]) {
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, & start);
	int i;
	if (getArraySize(argc, argv) == -1) { /*get the array size from command line */
		return -1;
	}
	array = malloc (sizeof(int) * ARRAYSIZE);
	pthread_t threads[P];

	//int array[ARRAYSIZE];
	
	for(i = 0; i < P; ++i) {
		int *arg = malloc(sizeof(*arg));
		*arg = i;
		if(pthread_create(&threads[i], NULL, populateArray, arg)) {
			perror("pthread create: ");
			exit(1);
		}
	}
	void *retVal;
	for(i=0; i < P; ++i) {
		pthread_join(threads[i], &retVal);
	}

/*	for (i = 0; i < ARRAYSIZE; i++) {
		array[i] =rand();
		print to check random numbers are random 
		printf("array index %d has value: %d\n", i, array[i]); 
	}*/
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Elapsed time for array of size %i : %f\n", ARRAYSIZE, elapsed);
	return 0;
}

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

void * populateArray(void *x) {
	int thread = *((int*) x);
	free(x);
	double base = floor((double)(ARRAYSIZE/4));
	int start, end; //index
	switch (thread) {
		case 0:
			/*printf("thread value is: %d\n", thread);*/
			start = 0;
			end = (int)floor(ARRAYSIZE/4);
			for (start=start; start <= end; start++) {
				array[start] = 0;
			}
			break;
		case 1:
			start = (int)floor(ARRAYSIZE/4) + 1;
			end = (int)floor(ARRAYSIZE/2);
			for (start=start; start <= end; start++) {
				array[start] = 1;
			}
			/*printf("thread value is: %d\n", thread);*/
			break;
		case 2:
			start = (int)floor(ARRAYSIZE/2) + 1;
			end = base*3;
			/*printf("thread value is: %d\n", thread);*/
			for (start=start; start <= end; start++) {
				array[start] = 2;
			}
			break;
		case 3:
			start = base*3 + 1;
			end = ARRAYSIZE-1;
			/*printf("thread value is: %d\n", thread);*/
			for (start=start; start <= end; start++) {
				array[start] = 3;
			}
			break;
		default:
			printf("something is wrong\n");


	}

	pthread_exit(0);
}