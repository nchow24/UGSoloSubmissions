//Nicole Chow	nchow24	(250725575)
//Nov. 5, 2017
//Header file for Part 1

extern int x;
extern int y;
extern int z;

//calculates z = x = y
void *calculate() {
	printf("parent created thread\n");
	printf("thread computing z = x + y\n");
	z = x + y;
	printf("thread's z value: %d\n", z);
	printf("thread has completed\n");
	return NULL;
}