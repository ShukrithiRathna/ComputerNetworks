//Chat-Server
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
	char msg[256];
	char recm[256];

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
	
	while(1)
	{
// sending a message to the client
		printf("\nServer:");//prompt
   		gets(msg);//get msg from user input (server side)
    	int s=send(clientfd,msg,sizeof(msg),0);// fd of accepted connection (client) not original or server. Returns the #bytes sent.
//read msg from client
		int reader=read(clientfd,&recm,sizeof(recm));//reads total number of chars in soket or 255. returns total #chars
		printf("\nClient:%s",recm);
		if(strcmp(msg,"Bye")==0&& strcmp(msg,recm)==0)//both server and client say "Bye" => end of chat
    	{
    	      printf("\nEnd of chat");
    	      break;
    	}
    }
	close(serverfd);//use fd of server to close connection
	return (0);
}
