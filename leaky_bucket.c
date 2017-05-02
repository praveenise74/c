#include<stdio.h>
#include<stdlib.h>
#define size 512
void bucket(int a,int b)
{
 if(a>size)
  printf("\n Bucket overflow!!\n");
 else
  {
   sleep(1);
   while(a>b)
   {
    printf("\nNumber of byte sent is %d\n",b);
    a-=b;
    sleep(1);
   }
   if(a>0)
    printf("\nLast byte sent is %d\n",a);
   printf("\nBucket output is successfull\n");
  }
}
void main()
{
  int op,pkt,i;
  printf("\nEnter output rate : ");
  scanf("%d",&op);
  for(i=0;i<5;i++)
  {
   sleep(1);
   pkt=rand()%600;
   printf("\n\nNew packet size is %d",pkt);
   //scanf("%d",&pkt);
   bucket(pkt,op);
  }
}

