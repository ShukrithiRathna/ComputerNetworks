//File transfer Client 
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<netdb.h>

int main()
{

	int socket_client;
	socket_client=socket(AF_INET,SOCK_STREAM,0);//creating a socket
	char msg[256];
	char recm[256];

//Server structure
	struct sockaddr_in serv_addr;//sockaddr_in -structure containing internet address. defined in <netinet.h>
	serv_addr.sin_family=AF_INET;//address family
	serv_addr.sin_port=htons(9002);//port number-convert from host byte order to network byte order using htons()
	serv_addr.sin_addr.s_addr=INADDR_ANY;//IP address of the host. For server-address of local machine-constant 

//Connecting to the server
	int con=connect(socket_client,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(con==-1)
		printf("\nConnection failed");
//Receiving contents of file from server
	int reader=recv(socket_client,&msg,sizeof(msg),0);
		if(reader==-1)
			printf("\nReceiving failed");

	FILE * fp=fopen("RTestFile.txt","w");//Opening new file
	fprintf(fp,"%s",msg);//writing into the file
	printf("\nContents of file sent by server have been written into new file\n");

	close(socket_client);//close socket
	fclose(fp);//close the file
	return (0);
}
