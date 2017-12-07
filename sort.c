#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

void swap(int *v1,int *v2)
{
  int t=*v1;
   *v1=*v2;
    *v2=t;
}

void bubble_sort(int arr[],int len)
{
  int i,j;
  for(i=0;i<len-1;i++)
   for(j=0;j<len-i-1;j++){
    if(arr[j]>arr[j+1])
     swap(&arr[j],&arr[j+1]);
	}
}

int get_array(int index_from_array[], int index_to_array[], int gather_array[], int num_array)
{
  int min_value=99999, min_array=-1,i;
  for(i=0;i<num_array;i++)
   {
    if(gather_array[index_from_array[i]] < min_value && index_from_array[i] < index_to_array[i])
     {
      min_value=gather_array[index_from_array[i]];
      min_array=i;
    }
  }
  return min_array;
}

int main(int argc,char *argv[])
{
 int n,part,rank,size,i,array[20],scatter_array[20],gather_array[20],sorted_array[20];
 FILE *f;
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 
 if(rank==0)
	{
	n=20;
	if(n%size!=0)
		{
			printf("number of processor shoud be factor of n\n");
			exit(-1);
		}
	
	f=fopen("number.txt","r");
	for(i=0;i<n;i++)
	fscanf(f,"%d",&(array[i]));
	fclose(f);
	printf("\nELEMENT STORED IN FILE\n\n");
	for(i=0;i<n;i++)
	{
	printf("data = %d\n",array[i]);
	}
	}

MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

MPI_Barrier(MPI_COMM_WORLD);

part=n/size;

MPI_Scatter(array,part,MPI_INT,&scatter_array,part,MPI_INT,0,MPI_COMM_WORLD);
printf("\nRANK == %d SIZE == %d\n",rank,part);
for(i=0;i<part;i++)
{
printf("\nDATA == %d\n",scatter_array[i]);
 }

MPI_Barrier(MPI_COMM_WORLD);

bubble_sort(scatter_array,part);

MPI_Barrier(MPI_COMM_WORLD);
printf("\nAfetr bubble_sort\n");
printf("RANK == %d\n",rank);
for(i=0;i<part;i++)
 printf("RANK==%d DATA=%d\n",rank,scatter_array[i]);


MPI_Gather(scatter_array,part,MPI_INT,gather_array,part,MPI_INT,0,MPI_COMM_WORLD);

if(rank==0)
{
int array;
 int index_from_array[size],index_to_array[size],index=0;

 for(i=0;i<size;i++){
	index_from_array[i]=i*part;
	index_to_array[i]=index_from_array[i]+part;
	}

	while(1)
	{
		
		if((array=get_array(index_from_array, index_to_array, gather_array, size))==-1)break;
		
		sorted_array[index++]=gather_array[index_from_array[array]];
		index_from_array[array]++;
	}

	printf("Sorted array:-");
	for(i=0;i<n;i++)
		printf("\nDATA == %d",sorted_array[i]);

	f=fopen("resuk.txt","w");
	for(i=0;i<n;i++)
	fprintf(f,"%d\n",sorted_array[i]);
	close(f);
}
MPI_Finalize();
return 0;
}	
