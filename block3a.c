#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
 int rank,p,tag=1,count=0,rc;
 char inmsg,outmsg='x';
 MPI_Status stat;
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 MPI_Comm_size(MPI_COMM_WORLD,&p);
 
 if(rank==0)
	{
		if(p>2)
		printf("Total no. of processor is %d nedded only two 2 ignoring extra",p);
		
		rc=MPI_Send(&outmsg,1,MPI_CHAR,1,tag,MPI_COMM_WORLD);
		rc=MPI_Recv(&inmsg,1,MPI_CHAR,1,tag,MPI_COMM_WORLD,&stat);
	}
 if(rank==1)
	{
		rc=MPI_Send(&outmsg,1,MPI_CHAR,0,tag,MPI_COMM_WORLD);
		rc=MPI_Recv(&inmsg,1,MPI_CHAR,0,tag,MPI_COMM_WORLD,&stat);
	}

 if(rank<2)
	{
		MPI_Get_count(&stat,MPI_CHAR,&count);
		printf("\ntask %d send %c char(s) to task %d  with tag %d \n",rank,inmsg,stat.MPI_SOURCE,stat.MPI_TAG);
	}
 MPI_Finalize();
}

