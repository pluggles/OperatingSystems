/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 3 - Problem 2
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 10/06/15
*************************************************/

/*Threading problem */
#include <stdio.h>

int getArraySize (int, char **);

int ARRAYSIZE;

int main(int argc, char *argv[]) {
	if (getArraySize(argc, argv) == -1) {
		return -1;
	}




	return 0;
}

int getArraySize (int argc, char *argv[]) {
	
	char badChar;
	if (argc != 2) {
		printf("Error ussage is: %s [Number]\n", argv[0]);
		return -1;
	} else if (sscanf (argv[1], "%i %c", &ARRAYSIZE, &badChar)!=1) {
		printf("Please enter a valid integer\n");
		return -1;
	} else if (ARRAYSIZE <= 0) {
		printf("Please enter a valid positive integer\n");
		return -1;
	} else {
		return 0;
	}

}
