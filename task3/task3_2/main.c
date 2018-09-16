#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>
#include <signal.h>
#include <string.h>
#include <setjmp.h>
#include <time.h>
#include <pthread.h>
#include<sys/time.h>
#include <unistd.h>
#include "mylib.h"

pthread_t thread1;
pthread_t thread2;
pthread_t thread3;
pthread_t thread4;
pthread_t thread5;

int returnvalue[5];
int ret;
int countsig=0;
//function for signal handler
void signal_handler(int signo)
{
	countsig++;
	printf("\n********************************************");
	printf("\nInsider the signal Handler");
	//signalHandlerFlag = 1;
	if (signo == SIGUSR1)
       		printf("\nreceived SIGUSR1\n");
   	 else
        	printf("\n did not receive the signal but inside handler\n");
	long int pid=pthread_self();
  	if (pid==thread1)
  	printf("\nSignal Handler called for thread 1 with ");
  	if (pid==thread2)
  	printf("\nSignal Handler called for thread 2 with ");
  	if (pid==thread3)
  	printf("\nSignal Handler called for thread 3 with ");
  	if (pid==thread4)
  	printf("\nSignal Handler called for thread 4 with ");
	if (pid==thread5)
  	printf("\nSignal Handler called for thread 5 with ");
	printf("\n********************************************");

  return;
}
//Thread functions for each thread
void* threadfun1(void *data)
{ 
      	  printf("\nThread1 with thread id %lu created\n", pthread_self() );
          ret=registerthread(1);		//command to register with the library
	  //printf("\n 1 %d",ret);
	  returnvalue[0]=ret;
	 usleep(1000);				//different sleep time for each thread
	  pthread_exit(NULL);
}

void* threadfun2(void *data)
{ 
      	  printf("\nThread2 with thread id %lu created\n", pthread_self() );
          ret=registerthread(2);
	  //printf("\n 2 %d",ret);
	   returnvalue[1]=ret;
	 usleep(1250);
	 pthread_exit(NULL);
}

void* threadfun3(void *data)
{ 
      	  printf("\nThread3 with thread id %lu created\n", pthread_self() );
          ret=registerthread(3);
	  //printf("\n 3 %d",ret);
	   returnvalue[2]=ret;
	  usleep(1700);
	  pthread_exit(NULL);
}

void* threadfun4(void *data)
{ 
          printf("\nThread4 with thread id %lu created\n", pthread_self() );
          ret=registerthread(4);
	  //printf("\n 4 %d",ret);
	   returnvalue[3]=ret;
	  usleep(1900);
	 pthread_exit(NULL);
}

void* threadfun5(void *data)
{ 
          printf("\nThread5 with thread id %lu created\n", pthread_self() );
          ret=registerthread(5);
	  //printf("\n 5 %d",ret);
	   returnvalue[4]=ret;
	 usleep(2150);
	  pthread_exit(NULL);
}

int main()
{
	  //intialization for signal handler
	  int value,ret;
	  pthread_t thread1;
	struct sigaction action;
	sigset_t block_mask;
	// pthread_t thread2;
	  memset(&action,0,sizeof(action));
	  sigfillset(&block_mask);
	  action.sa_handler = signal_handler;
	  action.sa_mask = block_mask;
	  sigaction(SIGUSR1, &action, NULL);
   a1:	printf("\nEnter the threads you want to register");
	scanf("%d",&value);
	ret=savecount(value);
	if(ret<0)
	{
		printf("\n Invalid Arguments");
		goto a1;
	}
	//thread creation
	pthread_create(&thread1,NULL, threadfun1, NULL);
	printf("\n Pthread id for thread 1 = %lu",thread1);
	pthread_create(&thread2,NULL, threadfun2, NULL);
	printf("\n Pthread id for thread 2 = %lu",thread2);
	pthread_create(&thread3,NULL, threadfun3, NULL);
	printf("\n Pthread id for thread 3 = %lu",thread3);
	pthread_create(&thread4,NULL, threadfun4, NULL);  
	printf("\n Pthread id for thread 4 = %lu",thread4);	
	pthread_create(&thread5,NULL, threadfun5, NULL);  
	printf("\n Pthread id for thread 5 = %lu",thread5);
	//sending the signal to the threads who have registered
	if(returnvalue[0]==1)
	{
	  pthread_kill(thread1,SIGUSR1);
	  usleep(500);
	}

	if(returnvalue[1]==1)
	{
	  pthread_kill(thread2,SIGUSR1);
	  usleep(500);
	}

	if(returnvalue[2]==1)
	{
	  pthread_kill(thread3,SIGUSR1);
	  usleep(500);
	}
	
	if(returnvalue[3]==1)
	{
	  pthread_kill(thread4,SIGUSR1);
	  usleep(500);
	}

	if(returnvalue[4]==1)
	{
	  pthread_kill(thread5,SIGUSR1);
	  usleep(500);
	}
        pthread_join(thread1,NULL); 
	pthread_join(thread2,NULL); 
	pthread_join(thread3,NULL); 
        pthread_join(thread4,NULL); 
	pthread_join(thread5,NULL); 
	sleep(1);
	printf("\n Count is %d",countsig);
	return 0;
}
