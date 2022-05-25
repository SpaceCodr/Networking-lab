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
    int sockfd,len,valread;
    struct sockaddr_in address,cliaddr;
    int addrlen = sizeof(address);
    char buffer[1024];
    char* hello="Hello from server";

    //Creation socket file descriptor
    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket failed");
        return 0;
    }
    printf("Socket Created\n");

    //memset(&address,0,sizeof(address));
    //memset(&cliaddr,0,sizeof(cliaddr));

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(8080);
    //Bind address to socket
    if (bind(sockfd,(const struct sockaddr*)&address,sizeof(address))<0)
    {
        perror("bind failed");
        return 0;
    }
    printf("Binded\n");
    len=sizeof(cliaddr);
    valread=recvfrom(sockfd,(char *)buffer,1024,MSG_WAITALL,(struct sockaddr*)&cliaddr,&len);
    buffer[valread]='\0';
    printf("Client:%s\n",buffer);
    sendto(sockfd,(const char *)hello,strlen(hello),MSG_CONFIRM,(struct sockaddr*)&cliaddr,len);
    printf("Hello message sent\n");
    //shutdown(server_fd,SHUT_RDWR);
    return 0;
}

