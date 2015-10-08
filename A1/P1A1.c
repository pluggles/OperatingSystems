/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 1 - Problem 1
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 09/21/15
*************************************************/


#include <stdio.h>

int main()
{
	//part 1
	double small = .5; //inclusive 0-1
	int large = 2500; //inclussive 10^3-10^6 [1000-1000000]

	printf("The sum of %.5f and %d is: %.5f\n", small, large, small+large);
	//part 2
	double *small_ptr = NULL;
	int *large_ptr = NULL;

	small_ptr = &small;
	large_ptr = &large;

	*small_ptr = .15;   // changes values of
	*large_ptr = 10000; // small and large
	printf("The value of small is %.5f and large is %d\n", small, large);
	printf("The value of small_ptr is: %p and large_ptr is: %p\n",
	 small_ptr, large_ptr);

	//part 3
	*small_ptr =-1;   // sets the values of small and large
	*large_ptr = -1;  // to set up while loop checking

    char input[40]; // arbitrary size buffer
    char* cp, badc; // badc is for detecting extraneous chars in the input
    int n;

   	printf("Please enter a value for small [0-1]:\n");
	while (small < 0){
		cp = fgets(input, sizeof(input), stdin);
			if (cp == input) {
				n = sscanf(input, "%lf %c", small_ptr, &badc);
				//printf("small is: %f\n", small);
				if(n != 1){
					printf("\nError please enter a valid number!:");
					*small_ptr = -1;
				} else if( small < 0 || small > 1) {
					printf("\nError please enter a valid number!:");
					*small_ptr = -1;
				}
			}
	}

	printf("Please enter a value for large [1000-1000000]:");
	while (large < 0){
		cp = fgets(input, sizeof(input), stdin);
			if (cp == input) {
				n = sscanf(input, "%d %c", large_ptr, &badc);
				//printf("small is: %f\n", small);
				if(n != 1){
					printf("\nError please enter a valid number!:");
					*large_ptr = -1;
				} else if(large < 1000 || large > 1000000) {
					printf("\nError please enter a valid number!:");
					*large_ptr = -1;
				}
			}
	}

	printf("\nThe value of small is %.5f and the value of large is %d\n\n",
	 small, large);
	
}