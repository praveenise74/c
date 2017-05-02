#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>

int main()
{
 struct sockaddr_in server_addr;
 int sock,byte_recv;
 char send_data[1024],recv_data[1024];

 if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
  {
    perror("erreor in socket:");
    exit(1);
  }
  

server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(6099);
server_addr.sin_addr.s_addr=inet_addr("127.0.01");

if(connect(sock,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
{
 perror("error at connet:");
 exit(1);
}
 
 printf("Enter file name to send");
 scanf("%s",send_data);

 send(sock,send_data,strlen(send_data),0);
 
 while((byte_recv=recv(sock,recv_data,1024,0))>0)
{
// byte_recv=recv(connect,recv_data,1024,0);
 recv_data[byte_recv]='\0';
 
 printf("receive data is %s",recv_data);
 
 if(strcmp(recv_data,"q")==0)
  {
   close(sock);
   break;
  }
}
return 0;
}
 

