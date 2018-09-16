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
pthread_t thread2;

struct timespec sleept, remain;
//thread function inside which the thread sleeps for some time
void threadfunc ( void *para)
{

 printf("\nWaiting to enter \n");
 
  sleept.tv_sec = 5;
  printf("\n going to sleep");
  nanosleep(&sleept,&remain);

  printf("\nExiting thread after interruped by the signal handler");
  pthread_exit(0);
}


//function for signal handler,the time left in the sleep is also printed inside in the function
void signal_handler(int signo)
{
	printf("\n******************************");
	printf("\nInsider the signal Handler");
	printf("\nTime Remaining is %d\n",(int)remain.tv_sec);
	if (signo == SIGUSR1)
       		printf("\nreceived SIGUSR1\n");
   	 else
        	printf("\n did not receive the signal but inside handler\n");
		//usleep(1000);
	 printf("\n******************************");
	return;
}

int main()
{
	  int i,j,k;
	 //initialiation for signal handler
	struct sigaction action;
	sigset_t block_mask;
	// pthread_t thread2;
	  memset(&action,0,sizeof(action));
	  sigfillset(&block_mask);
	  action.sa_handler = signal_handler;
	  action.sa_mask = block_mask;
	  sigaction(SIGUSR1, &action, NULL);
	 //Thread creation
	  pthread_create (&thread2, NULL, (void *) &threadfunc, NULL);
	  printf("\nstart:thread 1: %lu", thread2);
	  //loop to waste time before the signal is sent to the thread, try changing the time
	  for (i = 0; i < 1500; i++){

		for (j = 0; j < 200; j++)
		{
			for (k = 0; k < 100; k++)
			{
				
			}
		}
	 }
	 pthread_kill(thread2,SIGUSR1);
	 printf("\nsending signal\n");
	 pthread_join(thread2, NULL);
	 printf("\nExiting Main\n");

	 return 0;
}




	


