#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define SIZE 4

void fillmat(int m[SIZE][SIZE])
{
 int i,j;
 for(i=0;i<SIZE;i++)
 for(j=0;j<SIZE;j++)
  {
   scanf("%d",&m[i][j]);
  }
}

void printmat(int m[SIZE][SIZE])
{
 int i,j;
 for(i=0;i<SIZE;i++)
 {
	printf("|");
	for(j=0;j<SIZE;j++)
	{
	printf("%2d\t",m[i][j]);}
	printf("|\n");
 }
}

int main(int argc,char *argv[])
{
 int A[SIZE][SIZE],B[SIZE][SIZE],C[SIZE][SIZE],AR[SIZE][SIZE],CR[SIZE][SIZE],n=0;
  int myrank,p,from,to,i,j,k;

 //MPI_Status status;
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
 MPI_Comm_size(MPI_COMM_WORLD,&p);

 if(n%p!=0)
	{
	if(myrank==0)
		{
			printf("number of processor is not appropriate");
			MPI_Finalize();
			exit(-1);
		}
	}

  from=myrank*SIZE/p;
  to=(myrank+1)*SIZE/p;

  if(myrank==0)
	{
		printf("ENTER MATRIX A OF SIZE 4*4:\n");
		fillmat(A);
		printf("ENTER MATRIX B OF SIZE 4*4:\n");
		fillmat(B);
	}

  MPI_Bcast(B,SIZE*SIZE,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Scatter(A,SIZE*SIZE/p,MPI_INT,AR[from],SIZE*SIZE/p,MPI_INT,0,MPI_COMM_WORLD);

 printf("\nComputing slice %d (from row %d to %d)",myrank,from,to-1);
 for(i=from;i<to;i++)
 for(j=0;j<SIZE;j++){
 
		C[i][j]=0;
		for(k=0;k<SIZE;k++){
		C[i][j]+=AR[i][k]*B[k][j];
		}
	}

  MPI_Gather(C[from],SIZE*SIZE/p,MPI_INT,CR,SIZE*SIZE/p,MPI_INT,0,MPI_COMM_WORLD);

 if(myrank==0)
	{
		printf("\n\n");	
		printmat(A);
		printf("\n\n\t\t*\n");
		printmat(B);
		printf("\n\n\t\t=\n");
		printmat(CR);
	}
MPI_Finalize();
return 0;
}
