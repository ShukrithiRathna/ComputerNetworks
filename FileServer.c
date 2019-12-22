//File transfer Server
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
	int socket_server;//stores fd
	socket_server=socket(AF_INET,SOCK_STREAM,0);//creates new socket
	if(socket_server<0)
		printf("\nError opening socket");
	char msg[256];
	char recm[256];

//Server structure
	struct sockaddr_in serv_addr;//sockaddr_in -structure containing internet address. defined in <netinet.h>
	serv_addr.sin_family=AF_INET;//address family
	serv_addr.sin_port=htons(9002);//port number-convert from host byte order to network byte order using htons()
	serv_addr.sin_addr.s_addr=INADDR_ANY;//IP address of the host. For server-address of local machine-constant 

//Bind server to address
	int b=bind(socket_server,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(b==-1)
		printf("Binding not succesfull");
	listen(socket_server,5);
//Accepting connection
	int socket_client=accept(socket_server,NULL,NULL);
	
//Opening file
	FILE* fp=fopen("TestFile.txt","r");
	fgets(msg,256,fp);//Reading contents of the file
	printf("\n%s",msg);
//Sending contents of file to server	
	write(socket_client,msg,256);

    close(socket_server);
	fclose(fp);
	return (0);
}
