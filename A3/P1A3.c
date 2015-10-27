/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 3 - Problem 1
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 10/06/15
*************************************************/

#include <stdio.h>
#include <time.h>
#include <sys/sysinfo.h>

int getArraySize (int, char **);

int ARRAYSIZE;

int main(int argc, char *argv[]) {
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, & start);
	
	if (getArraySize(argc, argv) == -1) { /*get the array size from command line */
		return -1;
	}



	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Elapsed time for array of size %i : &d\n", ARRAYSIZE, elapsed);
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
