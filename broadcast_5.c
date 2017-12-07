#include<stdio.h>
#include<mpi.h>

 int main(int argc,char *argv[])
 {
 int rank,size,n,first,last,i;
 long long result=1,prod=1;
 
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 
 if(rank==0)
 {
  printf("\nEnter number to find factorial:");
  scanf("%d",&n);
 }

 MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
 first=rank*n/size;
 last=(rank+1)*n/size;

 for(i=first+1;i<=last;i++)
 	prod*=i;
 MPI_Reduce(&prod,&result,1,MPI_LONG_LONG,MPI_PROD,0,MPI_COMM_WORLD);
 
 if(rank==0)
  {
   printf("factorial of %d is %lld\n\n",n,result);
  }

 MPI_Finalize();
}

