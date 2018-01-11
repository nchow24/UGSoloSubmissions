//Nicole Chow	nchow24	(250725575)
//Nov. 5, 2017
//ReadyQueue class header for Part 2
//ReadyQueue structure has a priority level, queue to hold processes, and CPU scheduling algorithm

struct ReadyQueue {
	int priority;			//priority level
	int queue[10];			//queue for processes. queue[x] is the burst time for process number x + 1. eg queue[3] is process 4's burst time.
	char algorithm[64];		//CPU scheduling algorithm
	int timeQuantum;		//time quantum for rr algorithms
};