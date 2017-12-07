#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<string.h>

int main()
{
 int tid,cnt=0;
 FILE *f;
 char sword[100],filename[15]="jane.txt";

 #pragma omp parallel num_threads(2) firstprivate(cnt) shared(filename) private(sword,tid,f)
 {
 tid=omp_get_thread_num();
 #pragma omp sections
 {
 #pragma omp section
 {
  printf("Thread %d in section 1",tid);
  
  f=fopen(filename,"r");
  if(f)
   {
	while(!feof(f))
	{
	  fscanf(f,"%s",sword);
          if(feof(f))
		break;

	if(strcmp(sword,"jane")==0)
           cnt=cnt+1;
	printf("%s\n",sword);
	}

	printf("\nJane repeated %d number of times\n",cnt);
  }
 close(f);
 }

 #pragma omp section
  {
   printf("\nTHRED %d in section 2\n",tid);

   f=fopen(filename,"r");
   
   if(f)
    {
      while(!feof(f))
	{
         fscanf(f,"%s",sword);
          if(feof(f))
		break;
          
	 if(strcmp(sword,"elizabeth")==0)
		cnt=cnt+1;


	}
	printf("Elizabeth repeated %d number of times",cnt);
 }
 close(f);
}
}
}
}

	
         
