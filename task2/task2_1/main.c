#define _GNU_SOURCE
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#include<sched.h>


 
pthread_t thread1;
pthread_t thread2;
pthread_attr_t ptattr;
pthread_attr_t aptattr;
struct sched_param param1;
struct sched_param param2;
int flag=0;


//lower priority thread function
void *threadfun(void *args)
{	
	printf("Thread1 with thread id %lu created\n", pthread_self() );
	usleep(10000);	
	while(flag==0)
	{
	}
	if(flag==1)
		{
		printf("\nLower Priority Thread");
		}
	
	pthread_exit(NULL);
}
//higher priority thread function
void *threadfun1(void *args)
{	
	int i,j;
	printf("Thread2 with thread id %lu created\n", pthread_self());


	pthread_kill(thread1, SIGUSR1);
	//for loop for killing time to see if high priority thread runs first 
	for (i = 0; i < 1500; i++){

		for (j = 0; j < 2000; j++)
		{
			
		}
	}
	printf("\nExiting thread\n");
	
	pthread_exit(NULL);
}

//function for signal handler
void signal_handler(int signo){
	printf("\n**********************************");
	printf("\nInsider the signal Handler");
	
	if (signo == SIGUSR1)
	{
       		printf("\nreceived SIGUSR1\n");
		flag=1;
	}
   	 else
        	printf("\n did not receive the signal but inside handler\n");
		
	printf("\n**********************************");
	return;
}
int main()
{
	
	//initialiation for signal handler
	struct sigaction signal_handler_action;
	memset (&signal_handler_action, 0, sizeof (signal_handler_action));
	signal_handler_action.sa_handler = &signal_handler;
	if(sigaction(SIGUSR1, &signal_handler_action, NULL) == -1){
		printf("error occured\n");
	}
	param1.sched_priority = 20;
	param2.sched_priority = 80;

	//initialization of Thread attribute
	pthread_attr_init(&ptattr);
	pthread_attr_setinheritsched(&ptattr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&ptattr,SCHED_FIFO);
	pthread_attr_setschedparam(&ptattr, &param1);

	pthread_attr_init(&aptattr);
	pthread_attr_setinheritsched(&aptattr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&aptattr,SCHED_FIFO);
	pthread_attr_setschedparam(&aptattr, &param2);

	pthread_create( &thread1, &ptattr, &threadfun, NULL);
	pthread_create( &thread2, &aptattr, &threadfun1, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}
