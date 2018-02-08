#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREADS 5

void *printHello(void *threadid)
{
	long tid;
	tid=(long) threadid;
	printf("Hello World! It's me, the thread #%ld \n",tid);
	pthread_exit(NULL);
}

int main(int args, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	
	for(t=0; t<NUM_THREADS; t++)
	{
		printf("In main; creating thread %ld\n",t);
		rc=pthread_create(&threads[t],NULL,printHello,(void *) t);
		if(rc)
		{	
			printf("ERROR; return code form pthread_create() is %d\n",rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
//	return 0;
}
