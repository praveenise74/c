#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
        int data[50],frame[46],n,j=8,i,count=0,frsize,zeroadd=0;
        printf("How many bits you want to send?\n");
        scanf("%d",&n);
	printf("Enter bits : ");
        for(i=0;i<n;i++)
        scanf("%d",&data[i]);

        frame[0]=0;
        frame[1]=1;
        frame[2]=1;
        frame[3]=1;
        frame[4]=1;
        frame[5]=1;
        frame[6]=1;
        frame[7]=0;

        for(i=0;i<n;i++)
        {
         if(data[i]==0)
         {
          frame[j++]=data[i];
          count=0;
         }
        if(data[i]==1)
        {
         if(count==5)
         {
          frame[j++]=0;
          zeroadd++;
          frame[j++]=data[i];
          count=0;
         }
        else
        {
         frame[j++]=data[i];
         count++;
        }
        }
}

        frame[j++]=0;
        frame[j++]=1;
        frame[j++]=1;
        frame[j++]=1;
        frame[j++]=1;
        frame[j++]=1;
        frame[j++]=1;
        frame[j++]=0;
        frsize=n+16+zeroadd;

        printf("Frame sent is \n");
        for(i=0;i<frsize;i++)
        printf("%d\n",frame[i]);
        printf("At receiver site \n");
        for(i=0;i<n;i++)
        printf("%d",data[i]);
}

