#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
 int size,rank,sum=0,i,j,recv_buf[4],a[4][4],b[4],gather_buf[4];
 
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 
 if(rank==0)
 {
  printf("\nEnter matrix of size 4*4:\n");
  for(i=0;i<4;i++)
  for(j=0;j<4;j++){
     scanf("%d",&a[i][j]);
    }

  printf("\nEnter matrix of size 4*1\n");
   for(i=0;i<4;i++)
     scanf("%d",&b[i]);
 }

 MPI_Scatter(&a,4,MPI_INT,recv_buf,4,MPI_INT,0,MPI_COMM_WORLD);
 MPI_Bcast(&b,4,MPI_INT,0,MPI_COMM_WORLD);

 for(i=0;i<4;i++)
  {
    printf("\nmy rank = %d and recv_buf= %d",rank,recv_buf[i]);
  }
   
 for(i=0;i<4;i++)
  {
   printf("\nmy rank= %d and b=%d",rank,b[i]);
  }

 for(j=0;j<4;j++)
 {
  sum=sum+(recv_buf[j]*b[j]);
 }
 printf("\nRANK = %d and RESULT = %d ",rank,sum);
 MPI_Gather(&sum,1,MPI_INT,gather_buf,1,MPI_INT,0,MPI_COMM_WORLD);

 if(rank==0)
  {
   printf("\nOutput :-\n");
   for(i=0;i<4;i++)
    {
     printf("| %2d |\n",gather_buf[i]);
    }
  }

 MPI_Finalize();
}

