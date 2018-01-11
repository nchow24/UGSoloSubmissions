//Nicole Chow	nchow24	(250725575)
//Nov. 5, 2017
//Part 1 main

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "part1.h"

int x = 10;
int y = 20;
int z = 0;

int main(int argc, char *argv)
{

	pid_t pid;
	pid = fork();			//create child process

	//error in creating child
	if (pid < 0) {
		perror("fork");
		printf("\n main function: Unable to fork...errno number is %d\n", errno);
		exit(pid);

	//parent process 
	} else {
		if (pid > 0) {
			wait(NULL);

			//print parent's z value after child has calculated z
			printf("parent printing z...\nparent's z value: %d\n", z);

			pthread_t worker_thread;

			//create thread and call calcualte()
			if (pthread_create(&worker_thread, NULL, calculate(), NULL)) {
				fprintf(stderr, "Error while creating thread\n");
				exit(1);			}
			//print parent's z value after thread has calculated z
			printf("parent printing z...\nparent's z value: %d\n", z);

		//child process
		} else {
			printf("parent (PID %d) created child (PID %d)\n", getppid(), getpid());
			printf("child computing z = x + y\n");
			z = x + y;
			printf("child's z value: %d\n", z);
			printf("child has completed\n");
		}
	}

	return 0;
}
