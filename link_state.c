#include<stdio.h>
#include<string.h>
int main()
{
int count,src_router,i,j,k,w,v,min;
int cost_matrix[100][100],dist[100],last[100];
int flag[100];
printf("Enter number of routers\n");
scanf("%d",&count);
printf("Enter cost matrix value\n");
for(i=0;i<count;i++)
{
	for(j=0;j<count;j++)
	{
		printf("\n%d--->%d : ",i,j);
		scanf("%d",&cost_matrix[i][j]);
		if(cost_matrix[i][j]<0)
		cost_matrix[i][j]=999;
	}
}
printf("Enter source node\n");
scanf("%d",&src_router);
for(v=0;v<count;v++)
{
	flag[v]=0;
	
	dist[v]=cost_matrix[src_router][v];
}
flag[src_router]=1;
for(i=0;i<count;i++)
{
	min=999;
	for(w=0;w<count;w++)
	{
		if(!flag[w])
		if(dist[w]<min)
		{
			v=w;
			min=dist[w];
		}	
	}
	flag[v]=1;
	for(w=0;w<count;w++)
	{
		if(!flag[w])
		if(min+cost_matrix[v][w]<dist[w])
		{
			dist[w]=min+cost_matrix[v][w];

		}
	}
}
for(i=0;i<count;i++)
{
	printf("\n%d----->%d",src_router,i);
	
	printf("\n Shortest path cost=%d\n",dist[i]);
}
}

