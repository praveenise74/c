#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N strlen(g)
char t[128],cs[128],g[]="100000111";
int a,e,c;
void xor()
{
 for(c=1;c<N;c++)
  cs[c]=((cs[c]==g[c])?'0':'1');
}
void crc()
{
 for(e=0;e<N;e++)
  cs[e]=t[e];
 do
 {
  if(cs[0]=='1')
   xor();
  for(c=0;c<N-1;c++)
   cs[c]=cs[c+1];
  cs[c]=t[e++];
 }while(e<=a+N-1);
}
int main()
{
 printf("\n Enter data :");
 scanf("%s",t);
 printf("Generating polynomial is %s",g);
 a=strlen(t);
 for(e=a;e<a+N-1;e++)
  t[e]='0';
 printf("\nModified t[u] is %s\n",t);
 crc();
 printf("The checksum is %s\n",cs);
 for(e=a;e<a+N-1;e++)
  t[e]=cs[e-a];
 printf("The final codeword is %s",t);
 printf("\n test code detection 0(Yes) 1(No)?:");
 scanf("%d",&e);
 if(e==0)
 {
    printf("Enter position where error to be inserted :");
    scanf("%d",&e);
    t[e]=(t[e]=='0'?'1':'0');
    printf("Error data is %s \n",t);
 }
 crc();
 for(e=0;((e<N-1)&&(cs[e]!='1'));e++);
 if(e<N-1)
  printf("\n Error detected\n");
 else
  printf("\n no error detected\n");
 return 0;
}

