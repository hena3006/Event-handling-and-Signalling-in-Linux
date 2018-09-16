#include <stdlib.h>

pthread_mutex_t mutex;
int count=0;
int z=1;
int savecount(int a)
{
count=a;
if(count>4)
{
return -1;
}
printf("%d",count);
return 0;
}

int registerthread(int a)
{
	
	pthread_mutex_lock(&mutex);
	if(z<=count)
	{
	z++;
	pthread_mutex_unlock(&mutex);
	return 1;
	
	}
	else
	{
	pthread_mutex_unlock(&mutex);
	return 0;
	}
}


