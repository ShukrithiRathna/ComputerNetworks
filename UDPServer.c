/*
	Shukrithi Rathna
*/
// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define PORT     8080
#define MAXLINE 1024
 
// Driver code
int main() 
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
     
//creates new socket
   sockfd = socket(AF_INET, SOCK_DGRAM, 0)
   if(sockfd<0)
	{
		printf("\nError opening socket");
		return(0);	
	}	
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
     
//server structure
	struct sockaddr_in servaddr,cliaddr;//sockaddr_in -structure containing internet address. defined in <netinet.h>
	serv_addr.sin_family=AF_INET;//address family IPV4
	serv_addr.sin_port=htons(PORT);//port number-convert from host byte order to network byte order using htons()
	serv_addr.sin_addr.s_addr=INADDR_ANY;//IP address of the host. For server-address of local machine-constant 
     
    
//bind socket to address
	int b=bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(servaddr));
	if(b==-1)
	{
		printf("\nBinding not succesfull");
		return(0);
    }
    int len, n;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,( struct sockaddr *) &cliaddr,&len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
    printf("Hello message sent.\n"); 
    return 0;
}
