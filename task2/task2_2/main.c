#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <linux/input.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

sem_t m;
//thread function, it waits for the semaphore
void threadfunc ( void *para)
{

 printf("\nEntering the thread and going to wait \n");
 sem_wait(&m);       /* down semaphore */
 printf("\nExiting Thread After Post");
  pthread_exit(0);
}


//Function for signal handler
void signal_handler(int signo)
{
	printf("\n******************************");
	printf("\nInsider the signal Handler before post is called");
	//signalHandlerFlag = 1;
	if (signo == SIGUSR1)
       		printf("\nreceived SIGUSR1\n");
   	 else
        	printf("\n did not receive the signal but inside handler\n");
	 printf("\n******************************");
	return;
}

int main()
{
	  int i,j,k;
	  pthread_t thread1;
	struct sigaction action;
	sigset_t block_mask;
	//initialiation for signal handler
	  memset(&action,0,sizeof(action));
	  sigfillset(&block_mask);
	  action.sa_handler = signal_handler;
	  action.sa_mask = block_mask;
	  sigaction(SIGUSR1, &action, NULL);
	  

	sem_init(&m, 0, 0);
	//thread creation 
	pthread_create (&thread1, NULL, (void *) &threadfunc, NULL);
	printf("\nstart:thread 1: %lu", thread1);
	for(i=0;i<10000;i++)
	{
	}
	pthread_kill(thread1,SIGUSR1);
	//loop to kill time befor post signal is send, this is done to show that the thread waits for the post after completion of signal handler
	printf("\nsignal sent");
	for (i = 0; i < 1500; i++){

		for (j = 0; j < 1200; j++)
		{
			for (k = 0; k < 100; k++)
			{
				
			}
		}
	}
	
	sem_post(&m);
	pthread_join(thread1, NULL);
	printf("\nExiting Main\n");

	return 0;
}




	


