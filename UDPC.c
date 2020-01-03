/*
	Shukrithi Rathna
*/
// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<string.h>
 
#define PORT     8080
#define MAXLINE 1024
 
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;
 
//creates new socket
   sockfd = socket(AF_INET, SOCK_DGRAM, 0)
   if(sockfd<0)
	{
		printf("\nError opening socket");
		return(0);	
	}
 
    memset(&servaddr, 0, sizeof(servaddr));
     
//server structure
	struct sockaddr_in servaddr,cliaddr;//sockaddr_in -structure containing internet address. defined in <netinet.h>
	serv_addr.sin_family=AF_INET;//address family IPV4
	serv_addr.sin_port=htons(PORT);//port number-convert from host byte order to network byte order using htons()
	serv_addr.sin_addr.s_addr=INADDR_ANY;//IP address of the host. For server-address of local machine-constant 
     
    int n, len;
     
    sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("Hello message sent.\n");
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr,&len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    close(sockfd);
    return 0;
}
