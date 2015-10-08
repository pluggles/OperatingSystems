/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 1 - Problem 3
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 09/21/15
*************************************************/

#include <stdio.h>
#include <stdlib.h>

int sum = 0;
double mean = 0;

void calcEven(int*, int, int*, double*);
void calcOdd(int arr[], int length);


int main() {
	time_t t;
	srand((unsigned) time(&t));  //gen random seed
	int i, j, k, n;
	int arrAll[20];
	int arrEven[10];
	int arrOdd[10];   //init all arrays
	j = 0;
	k = 0;
	for (i=0; i < 20; i++){  //populate main array
		n = rand() % 10 + 1;
		arrAll[i] = n;
		if ( i % 2 == 0){  //populate even array
			arrEven[j] = n;
			j++;
		} else {  //populate odd array
			arrOdd[k] = n;
			k++;
		}
	}

	int *arrEven_ptr;
	arrEven_ptr = arrEven; //get pointer set up
	calcEven(arrEven_ptr, 10, &sum, &mean);  //calc even
	printf("\nSum of even array is: %d\n", sum);
	printf("Mean of even array is: %f\n", mean);
	mean = 0; //reset globals
	sum = 0;

	calcOdd(arrOdd, 10); //calc
}

void calcEven(int* arrPtr, int length, int* sum, double* mean) { 
	int i = 0;
	
	int sumTemp = *sum;  //dereferance
	for (i=0; i < length; i++){
		sumTemp += arrPtr[i]; //sum
	}
	*sum = sumTemp; //referance

	double meanTemp = *mean; //dereferance
	meanTemp = (double)sumTemp / length;  //mean
	*mean = meanTemp; //referance
	

}

void calcOdd(int arr[], int length){
	int i;
	for (i=0; i < length; i++){
		sum += arr[i];  //sum
	}
	mean = (double)sum / length;  //mean

		printf("\nSum of odd array is: %d\n", sum);
	printf("Mean of odd array is: %f\n", mean);
}