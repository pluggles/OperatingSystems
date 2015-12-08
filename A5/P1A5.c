/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 5 - Problem 1
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 12/11/15
*************************************************/

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
double estimatePi(int, int);
void * monteCarlo(void *);
/*number of points */
#define NR_PTS 1000000
/*Number of threads*/
#define NR_THREADS 10

/*All points within the circle */
int circleCount = 0;
/*the mutex*/
pthread_mutex_t count_mutex;
/* global seed time */
time_t seed; 
/* main() */
int main(int argc, char *argv[]) {
	int i;
	 /*create thread datatypes */
	pthread_t threads[NR_THREADS];
	/*init mutex */
	pthread_mutex_init(&count_mutex, NULL); 
	/* get first seed time */
	 seed = time(NULL); 
	/* for loop to create all threads */
	for(i = 0; i < NR_THREADS; ++i) { 
		/*get threadID */
		int *arg = malloc(sizeof(*arg)); 
		*arg = i;
		/*call thread method, passing id */
		if(pthread_create(&threads[i], NULL, monteCarlo, arg)) { 
			perror("pthread create: ");
			exit(1);
		}
	}
	
	for(i=0; i < NR_THREADS; ++i) {
		/* join the threads back */
		pthread_join(threads[i], NULL);
	}
	/* destroy the mutex */
	pthread_mutex_destroy(&count_mutex);
	/* call estimatePi finding Pi */
	printf("In the parent thread, estimated value of pi is: ");
	estimatePi(circleCount, (NR_THREADS*NR_PTS));
	return 0;
}
/* estimatePI (int pints, int totalPoints) */
/* calculates pi */
double estimatePi(int points, int totalPoints) {
	double pi = 4 * (((double)points) / (double)totalPoints);
	//printf("circle count is: %d\n", circleCount);
	printf("%lf\n", pi);
	return pi;
}
/* void * monteCarlo(Void *arg) */
/* the threading method, gets the thread Id */
/* finds x,y and decides if it is in the circle */
/* calculates pi for the thread */
/* increments the global circlecount */
void * monteCarlo(void *arg) {
	/* gets the thread id */
	int thread = *((int*) arg); 
	free(arg);

	double x, y;
	double min = -1.0;
	double max = 1.0;
	double range = (max - min); 
    double divisor = RAND_MAX / range;
	int counter = 0;
	int i;
	unsigned int threadSeed = seed + thread;

	for (i=0; i < NR_PTS; i++) {
			/* generate random points */
		x= min + ((double)rand_r(&threadSeed)/ divisor) ;
		y= min + ((double)rand_r(&threadSeed)/ divisor) ;
		/* see if points lie in cirlce */
		if ((x*x + y*y) <= 1) {
			/* if so incrment counter */
			counter++;
		}
	}
	/* get the thread estimate of of pi */
	printf("In thead %d Estimated value of pi is: ", thread);
	estimatePi(counter, NR_PTS);
	/* lock and update circleCount */
	pthread_mutex_lock(&count_mutex);
	circleCount += counter;
	pthread_mutex_unlock(&count_mutex);

	/*exit the thread */
	pthread_exit(0);
}