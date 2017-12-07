#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
void swap(int *v1,int *v2)
{
	int t=*v1;
	*v1=*v2;
	*v2=t;
}
void bubblesort(int *v,int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	for(j=0;j<n-i-1;j++)
	if(v[j]>v[j+1])
	swap(&v[j],&v[j+1]);
}
int *merge(int *v1,int n1,int *v2,int n2)
{
	int *result=(int *)malloc((n1+n2)*sizeof(int));
	int i=0,j=0,k;

	for(k=0;k<n1+n2;k++)
	{
		if(i>=n1)
		{
			result[k]=v2[j];
			j++;
		}
		else if(j>=n2)
		{
			result[k]=v1[i];
			i++;
		}
		else if(v1[i]<v2[j])
		{
			result[k]=v1[i];
			i++;
		}
		else
		{
			result[k]=v2[j];
			j++;
		}
	}
	 printf("IN MERGE value of n1 is %d and n2 is %d\n",n1,n2);

	for(i=0;i<n1+n2;i++)
	{
		printf("IN MERGE %d\n",result[i]);
	}
	return result;
}
int main(int argc,char **argv)
{
	int n,c,o,step,p,id,*data=NULL,*chunk,*other,i;
	double elapsed_time;
	FILE *file=NULL;
	
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	if(id==0)
	{
		n=20;
		if((n%p)!=0||(p%2)!=0)
		{

			printf("NUMBER OF PROCESSES SHOULD BE FACTOR OF 'n' and EVEN\n");
	        	exit(0);

		} 
		file=fopen("numbers.txt","r");

		data=(int *)malloc(20*sizeof(int));
		for(i=0;i<20;i++)
			fscanf(file,"%d",&(data[i]));
		fclose(file);
		for(i=0;i<20;i++)
			printf("data is %d\n",data[i]);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time=-MPI_Wtime();
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	c=n/p;
     
	printf("MY RANK == %d and size is %d\n",id,c);
	chunk=(int *)malloc(c*sizeof(int));
	MPI_Scatter(data,c,MPI_INT,chunk,c,MPI_INT,0,MPI_COMM_WORLD);
	free(data);
	
	data=NULL;


	printf("MY RANK == %d and size is %d\n",id,c);
	for(i=0;i<c;i++)
		printf("\nrank %d data =%d\n",id,chunk[i]);
	bubblesort(chunk,c);
	MPI_Barrier(MPI_COMM_WORLD);
	

	for(step=1;step<p;step=2*step)
	{
		if(id%(2*step)!=0)
		{
			MPI_Send(chunk,c,MPI_INT,id-step,0,MPI_COMM_WORLD);
			free(chunk);
			break;
		}
		if(id+step<p)
		{
			o=(n>=c*(id+2*step))?c*step:n-c*(id+step);
			printf("MY RANK = %d and o is %d\n",id,o);
			other=(int *)malloc(o*sizeof(int));
			MPI_Recv(other,c,MPI_INT,id+step,0,MPI_COMM_WORLD,&stat);
			data=merge(chunk,c,other,o);
			free(chunk);
			free(other);
			chunk=data;
			c=c+c;
			printf("\nRANK IS %d and CHUNK size is %d\n",id,c);
		}
	}
	
	elapsed_time += MPI_Wtime();
	if(id==0)
	{
		file=fopen("result.txt","w");
		for(i=0;i<20;i++)
			fprintf(file,"%d\n",chunk[i]);
		fclose(file);
		printf("Bubble sort %d ints on %d procs: %f secs\n",n,p,elapsed_time);
	}
	MPI_Finalize();
	return 0;
}

