//Nicole Chow	nchow24	(250725575)
//Dec. 8, 2017
//Client class header
//Client structure contains thread info (1 thread per client)

struct Client
{
	pthread_t thread;
	int err_thread;
};
