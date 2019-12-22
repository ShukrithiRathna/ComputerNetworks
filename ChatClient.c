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
//creates new  socket
	clientfd=socket(AF_INET,SOCK_STREAM,0);
	if(clientfd<0)
		printf("\nError opening socket");
	char msg[256];
	char recm[256];

//server structure
	struct sockaddr_in serv_addr;//socakddr_in -structure containing internet address. <defined in netinet.h>
	serv_addr.sin_family=AF_INET;//address family
	serv_addr.sin_port=htons(9002);//port number-convert from hbo to nbo using htons()
	serv_addr.sin_addr.s_addr=INADDR_ANY;//IP addres of the host. For server -address of loacl machine-constant.

//connect to the server
	int con=connect(clientfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(con==-1)
		printf("\n Connection failed");

    while(1)
    {
//read what server sends
		int reader=recv(clientfd,&msg,sizeof(msg),0);
		if(reader==-1)
			printf("receiving failed");
//displaying what server says
	    printf("\nServer:");
	    puts(msg);
//taking input from client
		printf("\nClient:");
		gets(recm);
//send received msg back to server
		int sent=send(clientfd,recm,sizeof(recm),0);
        if(strcmp(msg,"bye")==0 && strcmp(msg,recm)==0)
        {
            printf("\n the Chat ends bye bye!1");
            break;
        }
		if(sent==-1)
			printf("\n Sending failed");
    }
	close(clientfd);//close connection
	return (0);
}
