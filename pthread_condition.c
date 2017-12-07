#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>

bool data_availabel=false;
pthread_mutex_t lock = 	PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t data_avil_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t data_notavil_cond = PTHREAD_COND_INITIALIZER;
int buffer;

void *producer()
{
 int i;
 for(i=0;i<10;i++)
 {
  pthread_mutex_lock(&lock);
  
  while(data_availabel)
    pthread_cond_wait(&data_notavil_cond,&lock);
 
 buffer=i;
 printf("Producer : %d\n",buffer);
 data_availabel=true;
 pthread_cond_signal(&data_avil_cond);
 pthread_mutex_unlock(&lock);
 }
 printf("\nProducer Done\n");

//pthread_exit(NULL);
}

void *consumer()
{
 int i;
 for(i=0;i<10;i++)
  {
   pthread_mutex_lock(&lock);
   
  while(!data_availabel)
   	pthread_cond_wait(&data_avil_cond,&lock);

  printf("Consumer : %d\n",buffer);
  data_availabel=false;
  pthread_cond_signal(&data_notavil_cond);
  pthread_mutex_unlock(&lock);
 }
 printf("\nConsumer Done");

// pthread_exit(NULL);
}

int main()
{
 pthread_t prod,con;
 
 pthread_create(&prod,NULL,producer,NULL);
 pthread_create(&con,NULL,consumer,NULL);

 pthread_join(prod,NULL);
 pthread_join(con,NULL);

return 0;
}
