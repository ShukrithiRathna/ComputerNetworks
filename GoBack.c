/*
	10-09-18
	Shukrithi Rathna
*/
//Datalink layer Flow Control- Go Back N
/*
	This program takes the window size as input 
	and transmits packets accordingly, receiving	
	acknowledgement at the end of first frame and then
	after each packet accordingly. 
	Total number  of packets sent: winsize*4
	
*/
#include<stdio.h>
#include<string.h>

int main()
{
	int winsize,frame=0,ACK;
	printf("\nEnter Window size:");
	scanf("%d",&winsize);
	int i,j;
	for(i=1;i<=winsize*4;i++)
	{
		printf("\nPacket %d transmitted",i);
		if(i%winsize==0&&frame==0)//first frame is transmitted fully before receiving ack for first packet.
		{
			frame++;
			printf("\nWindow:");
			for(j=i-winsize+1;j<=i;j++)
			{
				printf("%d ",j);
			}
			printf("\nEnter ACK for packet %d (1 for yes, 0 for no):",i-winsize+1);
			scanf("%d",&ACK);
			if(ACK==0)
			{
				printf("\nRetransmitting packets");
				for(j=i-winsize+1;j<=i;j++)//retransmit all packets in current frame
				{
					printf("\nPacket %d retransmitted",j);
				}
				printf("\n");
			}
			
		}
		if(i>winsize)//after first frame, receive acknowlegement for every consecutive packet.
		{
			printf("\nWindow:");
			for(j=i-winsize+1;j<=i;j++)
			{
				printf("%d ",j);
			}
			printf("\nEnter ACK for packet %d (1 for yes, 0 for no):",i-winsize+1);
			scanf("%d",&ACK);
			if(ACK==0)
			{
				printf("\nRetransmitting packets");//retransmit all packets in current frame
				printf("\nWindow:");
				for(j=i-winsize+1;j<=i;j++)
				{
					printf("%d ",j);
				}
				for(j=i-winsize+1;j<=i;j++)
				{
					printf("\nPacket %d retransmitted",j);
				}
				printf("\n");
				
			}
			
		}
		
	}
	
	return(0);
}	
	
