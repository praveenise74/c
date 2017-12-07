#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t lock;
int buffer;

void *producer()
{
 int i;
 for(i=0;i<10;i++)
 {
  pthread_mutex_lock(&lock);
  
 buffer=i;
 printf("Producer : %d\n",buffer);
 pthread_mutex_unlock(&lock);
 }
 printf("\nProducer Done\n");

}

void *consumer()
{
 int i;
 for(i=0;i<10;i++)
  {
   pthread_mutex_lock(&lock);
   
  printf("Consumer : %d\n",i);
  pthread_mutex_unlock(&lock);
 }
 printf("\nConsumer Done");
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
