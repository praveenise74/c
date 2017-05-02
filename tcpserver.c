#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

int main()
{
struct sockaddr_in server_addr;
struct sockaddr_in client_addr;
FILE *fptr;
int sock,connected,byte_recv,sin_size;
char recv_data[1024],send_data[1024];
printf("before socket");
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
{
 perror("socket erreo:");
 exit(1);
}

server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(6099);
server_addr.sin_addr.s_addr=INADDR_ANY;
printf("before bind");
if((bind(sock,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)))==-1)
{
	perror("Error in bind:");
	exit(1);
}
printf("before listen");
if(listen(sock,5)==-1)
{
	perror("listen erreo:");
 	exit(1);
}

printf("TCP server waiting for client at port no. XXXX");
sin_size=sizeof(struct sockaddr_in);
connected=accept(sock,(struct sockaddr *)&client_addr,&sin_size);

while(1)
{
 byte_recv=recv(connected,recv_data,1024,0);
 recv_data[byte_recv]='\0';

 fptr=fopen(recv_data,"r");

 if(fptr==NULL)
  {
   strcpy(send_data,"FILE");
   send(connected,send_data,strlen(send_data),0);
  }

 while(!feof(fptr))
 {
  fscanf(fptr,"%s",send_data);
  send(connected,send_data,strlen(send_data),0);
 }
 strcpy(send_data,"q");
 send(connected,send_data,strlen(send_data),0);
 close(connected);
 break;
}

}
