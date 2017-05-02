#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void receiver();
char frames[1024];
int main()
{
        int i,n,len;
        char buffer[256],length[10];
        printf("enter no of frames\n");
        scanf("%d",&n);
        bzero(buffer,256);
        for(i=0;i<n;i++)
        {
                printf("enter data to frames %d\n",i+1);
                scanf("%s",buffer);
                len=strlen(buffer);
                len++;
                printf("length of frame %d is %d\n",i+1,len);
                sprintf(length,"%d",len);
                strcat(frames,length);
                strcat(frames,buffer);
        }
        printf("message send by the sender : ");
        for(i=0;frames[i]!='\0';i++)
                printf("%c",frames[i]);
                receiver();
}
void receiver()
{
        int i=0,framelen,lpvar;
        char leninchar;
        while(frames[i]!='\0')
        {
                leninchar =frames[i];
                framelen=(int)leninchar-(int)'0';
                printf("\n the length of frame is %d\n its contents are \n",framelen);
                lpvar=i+framelen;
                while(i<lpvar)
                        printf("%c",frames[i++]);
                printf("\n");
        }
}


