#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <setjmp.h>
#include <signal.h>
#include "rdtsc.h"

#define MOUSEFILE "/dev/input/event6"
jmp_buf buffer;
float pi = 0;
int flag = 0;
int pid_mouse;

void sig_handler(int signalNumber);
void* mouseFunction(void* ptr);
void* piFunction(void* ptr);
//main function
int main() {
	
	
	struct sigaction sa;
	// initialization of signal handler
	sa.sa_handler  = sig_handler;
	//sigemptyset(&sa.sa_mask);

	if(sigaction(SIGUSR1, &sa, NULL) == -1) {
		printf("Error in sigaction\n");
	}
	//thread creation
	pthread_t mouseThread, funcThread;
	
	pthread_create(&mouseThread, NULL, &mouseFunction, NULL);
	pthread_create(&funcThread, NULL, &piFunction, NULL);
	//set jump set
	if(setjmp(buffer) == 5)  {
		printf("\nImprecise value of pi is %.3f\n", pi);
		exit(0);
	}

	pthread_join(funcThread, NULL);
	pthread_join(mouseThread, NULL);
    
    return 0;
}
//mouse thread function to detect right click
void* mouseFunction(void* ptr) {
	
	int fd;
	struct input_event ie;
	pid_mouse = getpid();

	fd = open(MOUSEFILE, 0);
	if(fd == -1) {
		perror("opening device");
		exit(EXIT_FAILURE);
	}

	unsigned long long timeStamps[2];
	timeStamps[0] = timeStamps[1] = 0;

	while(flag != 1) {


		if(read(fd, &ie, sizeof(struct input_event))) {
			
			if(ie.code == 273 && ie.value == 1 ) {

				timeStamps[1] = rdtsc();
				if( (float)(timeStamps[1] - timeStamps[0])/2700000000 <= 0.3 ) {	
					
					printf("double click detected\n");
					kill(pid_mouse ,SIGUSR1);							
					break;
				}

				timeStamps[0] = timeStamps[1];								
				timeStamps[1] = 0;
			}			
		}		
	}
	return 0;
}
//function to calculate the pi
void* piFunction(void* ptr) {

	float k, s = 1;      	

	for(k = 1; k <= 800 ; k += 2) {
     	
     	pi = pi + s * (4 / k);
     	s = -s;
     	if(flag) {
     		longjmp(buffer, 5);		//use of long jump
     	}

     	usleep(50000);
   	}
   	printf("Precise value of pi is %.2f\n", pi);
   	return 0;
}
//signal handler here flag is set to 1 when handler is called
void sig_handler(int signalNumber) {
	printf("\n**********************************");
	printf("\nInsider the signal Handler");
	
	if (signalNumber == SIGUSR1)
	{
       		printf("\nreceived SIGUSR1\n");
		flag=1;
	}
   	 else
        	printf("\n did not receive the signal but inside handler\n");
		
	printf("\n**********************************");
	flag = 1;
}
