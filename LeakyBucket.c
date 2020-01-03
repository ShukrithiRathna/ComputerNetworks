/*
	CED16I031
	Shukrithi Rathna
	17-09-18
*/
/*
	Leaky Bucket algorithm implementation
	input: Number of packets,Packet size and Bucket Size
*/
#include<stdio.h>

int main()
{
		int n,i,bucksize,tempbs;
		printf("\nEnter total number  of packets");
		scanf("%d",&n);
		
		int pack[n];
		printf("\nEnter the size of the packets:");
		for(i=0;i<n;i++)
		{
			printf("\nPacket %d: ",i+1);
			scanf("%d",&pack[n]);
		}
		printf("\nEnter the size of the bucket:");
		scanf("%d",&bucksize);
		tempbs=bucksize;
		int j=0;
		i=0;
		
		while(1)
		{
			printf("\n Timer: %d",i++);
			while(1)
			{
				if(pack[j]<=tempbs)
				{
					tempbs-=pack[j];
					printf("\n Packet %dsent with size %d",j,pack[j++]);
				}
				else
				{
					printf("\nCannot send more refilling" );
					break;
				}
			printf("\n%d Last bucket size",tempbs );
			}
	
			tempbs=bucksize;
			if(j>=n)
			{
				printf("\nAll packets sent" );
				break;
			}
		}
				
	return(0);
}
