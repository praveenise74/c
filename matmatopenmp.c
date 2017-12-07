#include<stdio.h>
#include<omp.h>

int main()
{
 int r1,c1,r2,c2,i,j,k,a[10][10],b[10][10],res[10][10],tid;
 
 do{
 printf("Enter the size of matreix a:");
 scanf("%d%d",&r1,&c1);
 
 printf("Enter size of matrix b:");
 scanf("%d%d",&r2,&c2);
 
 if(c1!=r2)
  printf("\nPlease enter valid size\n");
 }while(c1!=r2);

 printf("\nEnter data for matrix a:\n");
 for(i=0;i<r1;i++)
 for(j=0;j<c1;j++){
  scanf("%d",&a[i][j]);
 }

 printf("\nEnter data for matrix b:\n");
 for(i=0;i<r2;i++)
 for(j=0;j<c2;j++){
  scanf("%d",&b[i][j]);
 }
 
for(i=0;i<r1;i++)
 for(j=0;j<c2;j++){
 res[i][j]=0;
  }
#pragma omp parallel num_threads(3) shared(a,b,res,r1,r2,c1,c2) private(i,j,k,tid)
{
 int tid=omp_get_thread_num();
  
  #pragma omp for 
  for(i=0;i<r1;i++)
   {
    printf("HI I AM THREAD %d and data = %d\n",tid,i);
     for(j=0;j<c2;j++)
      {
       for(k=0;k<c1;k++)
        {
         res[i][j]+=a[i][k]*b[k][j];
        }
    }
  }
}

printf("Result of matrix is:-\n");
 for(i=0;i<r1;i++){
 printf("\t|");
   for(j=0;j<c2;j++){
    printf("%2d\t",res[i][j]);
    }
     printf("|\n");
 }
return 0;
}
