//Nicole Chow	nchow24 (250725575) 
//Oct. 8, 2017
//Part 2 main

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>

int main()
{
	int n;
	int x;					// x value to be input from user in parent process
	int y;					// y value to be input from user in child process
	int fd[2];				// hold fds of both ends of pipe
	pid_t pid;				// pid of child process
	char line[80];			// used to read y from pipe

	// create a pipe and check if it is sucessful
	if (pipe(fd) < 0) {
		perror("pipe error\n");

	//pipe is sucessful	
	} else {
		printf("A pipe is created for communication between parent (PID %d) and child\n", getpid());

		//parent creates child and check if it is sucessful
		if ((pid = fork()) < 0) {
			perror("fork error\n");

		//fork is sucessful
		} else {
			//parent process
			if (pid > 0) {
				wait(NULL);

				//read x from user
				printf("From user, parent (PID %d) reading X = ", getpid());
				scanf("%d", &x);
				n = read(fd[0], line, 80);
				y = atoi(line);

				//read y from pipe and add x + y
				printf("parent (PID %d) reading Y from the pipe (Y = %d)\n", getpid(), y);
				int sum = x + y;
				printf("parent (PID %d) adding X + Y = %d\n", getpid(), sum);

			//child process
			} else {
				printf("parent (PID %d) created a child (PID %d)\n", getppid(), getpid());
				
				//read y from user
				printf("From user, child (PID %d) Reading Y = ", getpid());
				scanf("%d", &y);
				printf("child (PID %d) Writing Y into the pipe\n", getpid());

				//convert y to a string and write it to pipe
				char yNum[5];
				sprintf(yNum, "%d", y);
				write(fd[1], &yNum, sizeof(yNum));
			}
		}
	}

	return 0;
}