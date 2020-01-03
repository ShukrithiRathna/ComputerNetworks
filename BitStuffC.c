/*
	02-09-18
	Shukrithi Rathna
*/
//Datalink layer framin-Character Count
//Client side implementation

/*
	This program breaks up the msg received from client 
	into it's respective frames using the character count
	denoting start and finish that is given in the msg.
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

	int clientfd;//stores fd
	char msg[256];
	char recm[256],temp[100];
	char data[100];
	int fsize,i,j=0,count=0,flag;
	
//creates new  socket
	clientfd=socket(AF_INET,SOCK_STREAM,0);
	if(clientfd<0)
		printf("\nError opening socket");
	
//server structure
	struct sockaddr_in serv_addr;//socakddr_in -structure containing internet address. <defined in netinet.h>
	serv_addr.sin_family=AF_INET;//address family
	serv_addr.sin_port=htons(9002);//port number-convert from hbo to nbo using htons()
	serv_addr.sin_addr.s_addr=INADDR_ANY;//IP addres of the host. For server -address of loacl machine-constant.

//connect to the server
	int con=connect(clientfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(con==-1)
		printf("\n Connection failed");

//read what server sends
	int msglen=recv(clientfd,&msg,sizeof(msg),0);
	if(msglen==-1)
		printf("\nReceiving failed");

//displaying what server says
	printf("\nServer:");
	puts(msg);

//Removing bit stuffing
	for(i=5;i<msglen-5;i++)
	{
		data[i-5]=msg[i];//removing start of frame and end of frame
	}
	data[msglen-10]='\0';
	printf("Data:%s\n",data);
	int datalen=strlen(data);
	//printf("DL:%d",datalen);
	i=0;
	while(i<datalen)//traverse through string
	{
		if(data[i]=='1')//check for ED
		{
			for(j=i;j<i+4;j++)
			{
				if(data[j]=='0')//check for 0
				{
					flag=1;
					break;
				}	
				else
					flag=0;
			}
		}
		if(flag==0)//if 0 is found after, remove it
		{
			//printf("\nEntered flag at %d",i);
			for(j=i+5;j<datalen;j++)
			{
				temp[j-(i+5)]=data[j];//copy remaining data without stuffed bit to temp
			}
			//printf("\nTemp:%s",temp);
//			data[i+4]='0';
			for(j=i+4;j<datalen+1;j++)
			{
				data[j]=temp[j-(i+4)];//recopy to data, over-writing stuffed bit
			}
//			printf("D:%s",data);
			i=i+4;//increment by 4 to move pointer to after ED
			flag=1;
			datalen=datalen-1;//removed stuffed bit
			data[datalen]='\0';
		}
		else
			i++;
	}	
	printf("\nData after removing bit stuffing:%s",data); 
	close(clientfd);//close connection
	return (0);
}
