#include<stdio.h>
#include<mpi.h>
//#include<>

int main(int argc,char *argv[])
{
 int rank,p,prev,next,tag1=1,tag2=2;
 char send_buf[2],recv_buf[2];
 MPI_Status status[4];
 MPI_Request reqs[4];

 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&p);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 
 prev=rank-1;
 next=rank+1;
 
 if(prev<0)
	prev=p-1;
 if(next>=p)
        next=0;

 send_buf[0]='1';
 send_buf[1]='2';

 MPI_Isend(&send_buf[0],1,MPI_CHAR,next,tag1,MPI_COMM_WORLD,&reqs[0]);
 MPI_Irecv(&recv_buf[0],1,MPI_CHAR,prev,tag1,MPI_COMM_WORLD,&reqs[1]);

 MPI_Isend(&send_buf[1],1,MPI_CHAR,prev,tag2,MPI_COMM_WORLD,&reqs[2]);
 MPI_Irecv(&recv_buf[1],1,MPI_CHAR,next,tag2,MPI_COMM_WORLD,&reqs[3]);


 MPI_Waitall(4,reqs,status);

 printf("\ntask %d communicate with %d and %d ",rank,prev,next);

 MPI_Finalize();
}
