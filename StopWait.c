/*
	10-09-18
	Shukrithi Rathna
*/
//Datalink layer Flow Control-Stop and Wait
/*
	This program take total number of packets
	as input.
	After each packet is sent, user input is taken for acknowledgement
*/

#include<stdio.h>
#include<string.h>

int main()
{
	int total, ACK, count;
	printf("\nEnter Total number of packets:");//input number of packets
	scanf("%d",&total);
	int i;
	for(i=1;i<=total;i++)
	{
		printf("\nPacket %d transmitted",i);
		count++;
		printf("\nEnter ACK (1 for yes, 0 for no):");
		scanf("%d",&ACK);
		if(ACK==0)//retransmit if not received
		{
			printf("\nRetransmitted packet %d",i);
			count++;
		}
		
	}
	printf("\nTotal number of transmissions:%d",count);
	printf("\nNumber of retransmissions:%d",count-total);	
	return(0);
}	
	
