#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int rec[7],data[7],c1,c2,c3,c,i;
int main()
{
 printf("Enter the data bit by bit\n");
 scanf("%d%d%d%d",&data[0],&data[1],&data[2],&data[4]);
 data[6]=data[0]^data[2]^data[4];
 data[5]=data[0]^data[1]^data[4];
 data[3]=data[0]^data[1]^data[2];
 printf("The encoded bits are given below\n");
 for(i=0;i<7;i++)
 printf("%d",data[i]);
 printf("\n");
 printf("Enter the recieved data bits one by one :\n");
 for(i=0;i<7;i++)
 scanf("%d",&rec[i]);
 c1=rec[6]^rec[4]^rec[2]^rec[0];
 c2=rec[5]^rec[4]^rec[1]^rec[0];
 c3=rec[3]^rec[2]^rec[1]^rec[0];
 c=c3*4+c2*2+c1;
 if(c==0)
 printf("No error\n");
 else
 {
 printf("Error on the position %d\nand the correct message is\n",c);
 if(rec[7-c]==0)
 rec[7-c]=1;
 else
 rec[7-c]=0;
 for(i=0;i<7;i++)
 printf("%d",rec[i]);
 }
}


