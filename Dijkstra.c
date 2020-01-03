/*
	CED16I031
	Shukrithi Rathna
	17-09-18
*/

/*
	Dijktra's shortest path algo implentation
	Maximum 10 nodes in graph
	Input: Adjacency Matrix, starting node
	If no path exists-0
*/
	
#include<stdio.h>
#define INFINITY 9999
#define MAX 10
 
void dijkstra(int adj[MAX][MAX],int n,int startnode);
void dijkstra(int adj[MAX][MAX],int n,int startnode)
{
 
    int cost[MAX][MAX],distance[MAX],pred[MAX],visited[MAX];//pred[] stores the predecessor of each node
    int count,mindistance,nextnode;//count gives the number of nodes seen so far
    int i,j;
    
    //create the cost matrix
    for(i=0;i<n;i++)
    {
       for(j=0;j<n;j++)
       {
          if(adj[i][j]==0)
       	     cost[i][j]=INFINITY;
           else
               cost[i][j]=adj[i][j];
        }
    }
    
    printf("\nInitial distance from start node");
    
    for(i=0;i<n;i++)     //initialize pred[],distance[] and visited[]
    {
        distance[i]=cost[startnode][i];
        printf("\n Node %d: %d",i,distance[i]);
        pred[i]=startnode;
        visited[i]=0;
    }
    
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    while(count<n-1)
    {
        mindistance=INFINITY;
        
//nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
        {
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
            
         }   
//check if a better path exists through nextnode    
         visited[nextnode]=1;
         for(i=0;i<n;i++)
         {
         	if(!visited[i])
         	{
         		if(mindistance+cost[nextnode][i]<distance[i])//if new path via next node gives lower distance than update distance
         	   {
         		   distance[i]=mindistance+cost[nextnode][i];
         	      pred[i]=nextnode;
         	   }
         	}
//printing intermediate paths
         	if(i!=startnode)
         	{
         		printf("\n\nIntermediate after update");
		 	   printf("\nDistance of node %d = %d",i,distance[i]);
         	   printf("  Path= %d",i);
		 	   j=i;
         	   do
         	   {
         	       j=pred[j];
         	       printf("<-%d",j);
        		    }while(j!=startnode);
     		}	
         }
         count++;
    }
 	printf("\n\nFinal paths and distances");
//print the final paths and distances of each node from starting
    for(i=0;i<n;i++)
    {
        if(i!=startnode)
        {
            printf("\nDistance of node %d = %d",i,distance[i]);
            printf("\nPath= %d",i);
            j=i;
            do
            {
                j=pred[j];
                printf("<-%d",j);
            }while(j!=startnode);
        }
    }
    printf("\n");
}


int main()
{
    int adj[MAX][MAX];
    int i,j,n,start;
    
    printf("\nEnter no. of vertices: ");
    scanf("%d",&n);
    
    printf("\nEnter the adjacency matrix:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
     	{
     	       scanf("%d",&adj[i][j]);
     	}
     }
    printf("\nEnter the starting node:");
    scanf("%d",&start);
    dijkstra(adj,n,start);
    
    return 0;
}
 

