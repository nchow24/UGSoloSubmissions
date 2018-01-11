//Nicole Chow	nchow24	(250725575)
//Nov. 5, 2017
//Part 2 main

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "ReadyQueue.h"
#include "Process.h"


int main(){

//CREATING THE QUEUES ----------------------------------------------------------------------------------------------------------

	//create array of ReadyQueues
	struct ReadyQueue queues[3];
	int queueIndex = 0;

	//open input file for reading
	FILE * file;
	file = fopen("mullevel_queue_CPU_scheduling_input_file.txt", "r");

	//create ReadyQueues
	if (file != NULL) {
		char line[256];
		while (fgets(line, sizeof line, file) != NULL) {
			printf("CREATING READY QUEUE %d...\n", queueIndex + 1);

			//assign priority
			queues[queueIndex].priority = line[7] - '0';

			//assign CPU scheduling algorithm
			if (strstr(line, "fcfs")) {
				strcpy(queues[queueIndex].algorithm, "fcfs");
				queues[queueIndex].timeQuantum = 0;
			} else {
				if (strstr(line, "rr")) {
					strcpy(queues[queueIndex].algorithm, "rr");
					queues[queueIndex].timeQuantum = line[15] - '0';
				} else {
					strcpy(queues[queueIndex].algorithm, "sjf");
					queues[queueIndex].timeQuantum = 0;
				}
			}

			printf("Algorithm: %s\n", queues[queueIndex].algorithm);
			printf("Priority: %d\n", queues[queueIndex].priority);
			printf("Time Quantum (NULL if 0): %d\n", queues[queueIndex].timeQuantum);

			//get string of just the processes and burst times
			char *sub = strstr(line, "p1");
			int index = sub - line;
			char processes[256];
			strcpy(processes, &line[index]);

			//insert process burst times into queue of ReadyQueue
			printf("Adding procesess to queue...\n\n");
			char * token = strtok(processes, " ");
			int processIndex = 0;

			while (token != NULL) {
				if (!strstr(token, "p")) {
					queues[queueIndex].queue[processIndex] = atoi(token);
					processIndex++;
				}
				token = strtok(NULL, " ");
			}
			queueIndex++;
		}
	}

	printf("_________________________________________\n\n");
	fclose(file);

//EXECUTING THE QUEUES ----------------------------------------------------------------------------------------------------------

	int priorityQueue = 0;													//The queue that is being executed next
	int priority = sizeof(queues)/sizeof(queues[0]);						//The priority value that CPU will execute next
	int i, j, k, m;															//used in for loops

	for (i = 0; i < 3; i++) {

		//find the queue that will be executed next
		for (m = 0; m < 3; m++) {
			if (queues[m].priority == priority) {
				priorityQueue = m;
			}
		}
		priority--;
 

		printf("Executing READY QUEUE %d...\n", priorityQueue + 1);
		printf("Order of process execution:   ");

		//execute using fcfs
		if (strcmp(queues[priorityQueue].algorithm, "fcfs") == 0) {
			
			//order of execution is the order that processes arrive in, and processes arrive consecutively numbered from 1 - 10
			k = 0;
			for (k = 0; k < 10; k++) {
				printf("p%d  ", k + 1);
			}
			printf("\nWaiting time for each process:\n");

			//wait time for each process is the sum of the burst times for the processes before it
			int waitTime = 0;
			double avg = 0;													//average waiting time
			k = 0;
			for (k = 0; k < 10; k++) {
				avg = avg + waitTime;
				printf("p%d: %d\n", k + 1, waitTime);
				waitTime = waitTime + queues[priorityQueue].queue[k];
			}

			printf("Average waiting time: %.2f\n", avg /10);

		} else {
			//execute using rr
			if (strcmp(queues[priorityQueue].algorithm, "rr") == 0) {
				int quantum = queues[priorityQueue].timeQuantum;
				int completion[10] = { 0 };									//completion times for processes					
				int arrival[10] = { 0 };									//CPU arrival times  for procesess
				int completedAll = 0;										//whether all processes are completed
				int time = 0;												//used as a clock for CPU processing time
				int	timeProcessed;											//time CPU spends on a process		

				//copy ReadyQueue so burst times can be changed without affecting original values 
				struct ReadyQueue queueCopy = queues[priorityQueue];
				
				
				while (!completedAll){
					k = 0;
					for (k = 0; k < 10; k++) {

						//determine the amount of time CPU spends on process:
						if (queueCopy.queue[k] <= quantum) {
							timeProcessed = queueCopy.queue[k];
						} else {
							timeProcessed = quantum;
						}

						//update times for processes that aren't completed
						if (queueCopy.queue[k] > 0) {

							//recalculate turnaround times
							j = 0;
							for (j = 0; j < 10; j++) {
								if (queueCopy.queue[j] != 0) {
									completion[j] = completion[j] + timeProcessed;
								}

								if (arrival[k] == 0 && k != 0) {
									arrival[k] = time;
								}
							}

							//update time left for process
							queueCopy.queue[k] = queueCopy.queue[k] - timeProcessed;
							time = time + timeProcessed;
							printf("p%d  ", k + 1);
						}
					}

					//check if all processes are completed
					completedAll = 1;
					k = 0;
					for (k = 0; k < 10; k++) {
						if (queueCopy.queue[k] > 0) {
							completedAll = 0;
						}
					}
				}

				//turnaround time is completion time - arrival time
				printf("\nTurnaround time for each process:\n");
				k = 0;
				for (k = 0; k < 10; k++) {
					printf("p%d: %d\n", k + 1, completion[k] - arrival[k]);
				}

			//execute using sjf
			} else {
				struct Process processList[10];										//used to store processes in sjf order

				//store all processes in processList (not yet sorted)
				k = 0;
				for (k = 0; k < 10; k++) {
					struct Process process;
					process.number = k + 1;
					process.burst = queues[priorityQueue].queue[k];
					processList[k] = process;
				}

				//sort processList
				struct Process temp;
				j = 0;
				k = 0;
				for (j = 0; j<9; j++){
					for (k = 0; k<9; k++){
						if (processList[k + 1].burst < processList[k].burst){
							temp = processList[k];
							processList[k] = processList[k + 1];
							processList[k + 1] = temp;
						}
					}
				}

				//order of execution is the order of the sorted array (ascending)
				k = 0;
				for (k = 0; k < 10; k++) {
					printf("p%d  ", processList[k].number);
				}

				//wait time for each process is the sum of the burst times for the processes before it
				int waitTime = 0;
				double avg = 0;													//average waiting time
				k = 0;
				for (k = 0; k < 10; k++) {
					avg = avg + waitTime;
					printf("\np%d: %d", processList[k].number, waitTime);
					waitTime = waitTime + processList[k].burst;
				}
				printf("\nAverage waiting time: %.2f\n", avg / 10);

			}
		}
		printf("\n");
	}

	//time to process all queues is the sum of the burst times of all queues
	int timeTotal = 0;
	i = 0;
	j = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 10; j++) {
			timeTotal = timeTotal + queues[i].queue[j];
		}
	}
	printf("Total time to process all three queues: %d\n", timeTotal);

	return 0;
}