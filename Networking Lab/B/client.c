#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include <sys/types.h>

int main()
{
    int sockfd;
    char buffer[1024];
    char* hello="Hello from client";
    struct sockaddr_in servaddr;

    //Creation socket file descriptor
    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket failed");
        return 0;
    }
    printf("Socket Created\n");

    //memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8080);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    int len,n;
    sendto(sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
	printf("Hello message sent.\n");		
	n = recvfrom(sockfd, (char *)buffer, 1024,MSG_WAITALL, (struct sockaddr *) &servaddr,&len);
	buffer[n] = '\0';
	printf("Server : %s\n", buffer);
	
	close(sockfd);
	return 0;
}