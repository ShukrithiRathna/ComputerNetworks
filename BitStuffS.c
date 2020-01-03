/*
	02-09-18
	Shukrithi Rathna
*/
//Datalink layer framing-character count
//Server side implementation

/*
	This program takes as input the data to be
	sent to client performs the required bit stuffing before sending it to the client.
	ED-11111
	Stuffed bit-'0';
*/

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<netdb.h>

int main()
{
	int serverfd;//stores fd
	char data[100];
	char data2[100];
	char msg[100];
	char temp[100];
	int i,j,flag=1;
	
//creates new socket	
	serverfd=socket(AF_INET,SOCK_STREAM,0);
	if(serverfd<0)
		printf("\nError opening socket");
	
//server structure
	struct sockaddr_in serv_addr;//sockaddr_in -structure containing internet address. defined in <netinet.h>
	serv_addr.sin_family=AF_INET;//address family IPV4
	serv_addr.sin_port=htons(9002);//port number-convert from host byte order to network byte order using htons()
	serv_addr.sin_addr.s_addr=INADDR_ANY;//IP address of the host. For server-address of local machine-constant 

//bind server to address
	int b=bind(serverfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(b==-1)
		printf("binding not succesfull");

	listen(serverfd,5);//backlog queue or max connections allowed

//accepting connection
	int clientfd=accept(serverfd,NULL,NULL);//fd of new connection that is used after
	if(clientfd==-1)
		printf("\nConnection failed");
	else
		printf("\nConnection successful");


	printf("\nEnter data (in '1's and '0's) for frame:");
	scanf("%s",data);
	strcpy(data2,data);
	//printf("\nData:%s",data);
	i=0;
	int datalen=strlen(data);
	data[datalen]='\0';
	//printf("\nDL:%d",datalen);
	//printf("\nOriginal Data:%s",data2);		
	//printf("\nData:%s",data);

//Bit Stuffing
	while(i<datalen)//traverse through string
	{
		if(data[i]=='1')//check if string contains start ED
		{
			for(j=i;j<i+4;j++)
			{
				if(data[j]=='0')
				{
					flag=1;
					break;
				}	
				else
					flag=0;
			}
		}
		if(flag==0)//if chars are present
		{
			//printf("\nEntered flag at %d",i);
			for(j=i+4;j<datalen;j++)
			{
				temp[j-(i+4)]=data[j];//if chars are present
			}
			//printf("\nTemp:%s",temp);
			data[i+4]='0';
			for(j=i+5;j<datalen+1;j++)
			{
				data[j]=temp[j-(i+5)];//copy remaining string back to data
			}
			i=i+5;//increment by 5 to move  pointer to after stuffed bit
			flag=1;
			datalen=datalen+1;
			data[datalen]='\0';
		}
		else
			i++;
	}	
	printf("\nOriginal Data:%s",data2);		
	//printf("\nData:%s",data);
	//printf("\nDL:%d",datalen);
	data[datalen]='\0';
		
//Begin frame
	for(i=0;i<5;i++)
		msg[i]='1';

//Copy Data
	for(i=5;i<strlen(data)+5;i++)
	{
		msg[i]=data[i-5];
	}

//End frame
	j=strlen(data)+5;
	for(i=j;i<j+5;i++)
		msg[i]='1';
	
	int msglen=datalen+10;
	msg[msglen]='\0';
	char msg2[msglen];
	strcpy(msg2,msg);
	int	msg2len=strlen(msg2);
	//printf("\nMsg2 len %d\n",msg2len);
	//for(i=0;i<msglen;i++)
	//printf("\nMsg:%s\n",msg);
	
// sending  message to the client   	
    int s=send(clientfd,msg2,sizeof(msg2),0);// fd of accepted connection (client) not original or server. Returns the #bytes sent.
	if(s==-1)
		printf("\nSending failed");
	printf("\nMsg sent to  client after bit stuffing: %s\n",msg2);
	close(serverfd);//use fd of server to close connection
	return (0);
}
