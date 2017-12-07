#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
 int hdims=2,dims[2]={2,4},a,period[2]={0,0},rank,size,rank2,coord[2];
 MPI_Init(&argc,&argv);
 MPI_Comm newcomm;
// MPI_Comm_size(MPI_COMM_WORLD,&size);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 MPI_Cart_create(MPI_COMM_WORLD,hdims,dims,period,0,&newcomm);
 
 if(rank==0)
 {
  printf("\nEnter rank:");
  scanf("%d",&a);
  MPI_Cart_coords(newcomm,a,hdims,coord);
  printf("\nCoordinates are %d and %d\n",coord[0],coord[1]);
  printf("\nEnter Coordinates:");
  scanf("%d%d",&coord[0],&coord[1]);
  MPI_Cart_rank(newcomm,coord,&rank2);
  printf("\nRank is %d\n",rank2);
 }
 MPI_Finalize();
}
