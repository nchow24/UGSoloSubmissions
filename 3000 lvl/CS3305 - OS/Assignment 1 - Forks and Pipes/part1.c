//Nicole Chow	nchow24 (250725575) 
//Oct. 8, 2017
//Part 1 main


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	pid_t pid1;
	pid1 = fork();					//create child_1		
	wait(NULL);						//parent process waits until child_1 is complete
	
	//error - fork unsuccessful
	if (pid1 < 0) {
		perror("fork");
		printf("\n main function: Unable to fork...errno number is %d\n", errno);
		exit(pid1);
	} else {
		//parent process
		if (pid1 > 0) {


			pid_t pid2;
			pid2 = fork();				//parent process creates child_2
			wait(NULL);					//parent process waits for child_2 to complete
			//error - fork unsucessful
			if (pid2 < 0) {
				perror("fork");
				printf("\n main function: Unable to fork...errno number is %d\n", errno);
				exit(pid2);
			} else {
				//parent process
				if (pid2 > 0) {
					//do nothing
				//child_2
				} else {
					printf("parent (PID %d) created child_2 (PID %d)\n", getppid(), getpid());
					printf("child_2 (PID %d) is calling an external program B.out and leaving child_2...\n", getpid());
					execl("B.out",0);
				}
			}


		//child_1
		} else {
			printf("parent process (PID %d) created child_1 (PID %d)\n", getppid(), getpid());
			printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getppid(), getpid());
			pid_t pid11;
			pid11 = fork();								//child_1 creates child_1.1
			wait(NULL);									//child_1 waits for child_1.1 to complete
			//error - fork unsucessful
			if (pid11 < 0) {
				perror("fork");
				printf("\n main function: Unable to fork...errno number is %d\n", errno);
				exit(pid11);
			} else {
				//child_1 (parent of child_1.1)
				if (pid11 > 0) {
					printf("child_1 (PID %d) is now completed\n", getpid());
				//child_1.1
				} else {
					printf("child_1 (PID %d) created child_1.1 (PID %d)\n", getppid(), getpid());
				}
			}
		}
	}

	return 0;
}