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

sigset_t main_mask;

pthread_t thread1;
pthread_t thread2;
pthread_t thread3;
pthread_t thread4;  
pthread_t thread5; 
pthread_mutex_t mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//function for signal handler
void signal_handler(int signo)
{
	
  long int pid=pthread_self();
  printf("\n**********************************");
  printf("\nInsider the signal Handler");
	
  if (signo == SIGUSR1)
  {
       	printf("\nreceived SIGUSR1\n");
		
  }
  else
  printf("\n did not receive the signal but inside handler\n");
		
  if (pid==thread1)
  printf("\nSignal Handler called for thread 1 with ");
  if (pid==thread2)
  printf("\nSignal Handler called for thread 2 with ");
  if (pid==thread3)
  printf("\nSignal Handler called for thread 3 with ");
  if (pid==thread4)
  printf("\nSignal Handler called for thread 4 with ");
  if (pid==thread5)
  printf("\nSignal Handler called for thread 4 with ");
  printf("\n**********************************");
  return;

}
//thread function common for all threads, raise command is used to give signal to the thread from the function itself
void* threadfunc(void *data)
{ 
      	   int i;
	   for(i=0;i<2;i++)
	   {
	
           pthread_mutex_lock(&lock);
           raise(SIGIO); 
	   pthread_mutex_unlock(&lock);	
	   }	
           return 0;
}
     
int main()
{
 	
        struct sigaction action;
	int i;
	//thread creation
        pthread_mutex_init(&mutex, NULL);

       	pthread_mutex_lock(&lock);
	pthread_create(&thread1,NULL, threadfunc, NULL);
	printf("\n Pthread id for thread 1 = %lu",thread1);
	pthread_create(&thread2,NULL, threadfunc, NULL);
	printf("\n Pthread id for thread 2 = %lu",thread2);
	pthread_create(&thread3,NULL, threadfunc, NULL);
	printf("\n Pthread id for thread 3 = %lu",thread3);
	pthread_create(&thread4,NULL, threadfunc, NULL);  
	printf("\n Pthread id for thread 4 = %lu",thread4);
	pthread_create(&thread5,NULL, threadfunc, NULL);  
	printf("\n Pthread id for thread 5 = %lu",thread4);			
		

        //initialiation for signal handler
        memset(&action, 0, sizeof(action));
	action.sa_handler = signal_handler;
        action.sa_flags = SA_SIGINFO;
	sigaction(SIGIO, &action, NULL);
        sigemptyset(&main_mask);
        sigaddset(&main_mask,SIGIO);
	//masking the main process so that it doesnot receive the signal
         for (i=0;i<10;i++)

        {
	
	if(pthread_sigmask(SIG_BLOCK, &main_mask,NULL)!=0)
	{
	printf ("\nerror  ...");
	}
        
        }
	pthread_mutex_unlock(&lock);
		
          //Wait for each of the thread to terminate.
	  
                 pthread_join(thread1,NULL); 
		 pthread_join(thread2,NULL); 
		 pthread_join(thread3,NULL); 
          	 pthread_join(thread4,NULL); 
		 pthread_join(thread5,NULL);
	printf("\n");
	return 0;
}
