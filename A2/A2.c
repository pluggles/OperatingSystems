/*************************************************
* Course CS 4540 - Spring 2015
* Assigmnet 2 - A2.c
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* submitted: 10/19/2015
*************************************************/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 256
#define READ_END 0
#define WRITE_END 1

int checkPassword(char *str);
void readStr(int fd, char *destination);


int main(void){
	
	int fd1[2], fd2[2]; /* file descriptors for pipe */
	pid_t pid;
	char *userInput = malloc(BUFFER_SIZE * sizeof(char));
	char *passwordStrength = malloc(BUFFER_SIZE * sizeof(char));
	/*printf("process ID of main is: %d\n", getpid()); */
	/* Ask the user for */
	/* create both the pipes */
	
	if(pipe(fd1) == -1) {
		fprintf(stderr, "Pipe failed");
		return 1;
	}

	if(pipe(fd2) == -1) {
		fprintf(stderr, "Pipe failed");
		return 1;
	}

	pid = fork();  /* fork the procs */
	switch (pid) {
		case -1: /* forking error */
			fprintf(stderr, "Fork failed");
			return 1;
	
		case 0:  /* child */
			
			close(fd1[WRITE_END]);
			close(fd2[READ_END]);
			readStr(fd1[READ_END], userInput);
			printf("Child(%d) checking password strength..\n", getpid());
			int isValidPass = checkPassword(userInput);
			if (isValidPass == 0) {
	   			passwordStrength = "short password\n";
	   		} else if (isValidPass == 1) {
	   			passwordStrength = "strong password\n";
	   		} else {
	   			passwordStrength = "weak password\n";
	   		}
			close(fd2[READ_END]);
			printf("Child(%d) found password strength sending to parent\n", getpid());
			write(fd2[WRITE_END], passwordStrength, strlen(passwordStrength));
			close(fd1[WRITE_END]);
			/* wait for parent process to exit */
			wait(NULL);
			
	   	break;

	   	default: /* parent */
	   		
	   		// ask the user for their password */
	   		fprintf(stdout, "Parent(%d): Enter your password: ", getpid());
	   		scanf("%s", userInput);

	   		/* close the read/write ends of the pipes no longer needed */
	   		close(fd1[READ_END]);
	   		close(fd2[WRITE_END]);
			
			/* write the input to the pipe */
			write(fd1[WRITE_END], userInput, strlen(userInput));

			/*close the write end of the pipe */
			close(fd1[WRITE_END]);
			readStr(fd2[READ_END], passwordStrength);
			printf("Parent(%d): %s", getpid(), passwordStrength);
            




	}
	//printf("process ID of main is: %d\n", getpid());
	free(userInput);
	return 0;
	
}

/*reads the user in put string and checks its strenght
* int hasUpper, hasLower, hasNumber, isLong used to check requierments
* retruns 0 for not long enough, 1 for strong, 2 for weak
*/
int checkPassword(char *str) {
	int hasUpper = 0;
	int hasLower = 0;
	int hasNumber = 0;
	int isLong = 0;
	isLong = (int)strlen(str); /* get the length of the user input */
	while (*str != '\0') {  /* checks each character in the string */
		if (islower(*str)) {  /* check for lower case letter */
			hasLower = 1;
		}
		if (isupper(*str)) {  /* check for upper case letter */
			hasUpper = 1;
		}
		if (isdigit(*str)) { /* checks for number */
			hasNumber = 1;
		}
				++str; /* increment character being checked */
	}

	if (isLong < 8) {
		return 0;
	} else if (hasLower && hasUpper && hasNumber) {
		return 1;
	} else {
		return 2;
	}
}


void readStr(int fd, char *destination) {
	int i = 0;
	/*read from pipe while not eof */
	while (read(fd, &destination[i], 1) > 0) {
		++i;
	}

	destination[i] = '\0'; /* gotta terminate the string */
}