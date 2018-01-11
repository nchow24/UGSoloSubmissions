//Nicole Chow	nchow24	(250725575)
//Nov. 5, 2017
//Process class header for Part 2
//Process structure contains a process number and burst time
//Used for processing sjf when sorting a Readyqueue.queue (since index can no longer be used for process number when sorting array)

struct Process
{
	int number;				//process number
	int burst;				//process burst
};
