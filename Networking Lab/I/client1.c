#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    int sock=0,client_fd,valread;
    struct sockaddr_in serv_addr;
    int addrlen = sizeof(serv_addr);
    int hel=5;

    //Creation socket file descriptor
    if ((sock=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket failed");
        return 0;
    }
    printf("Socket Created\n");
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(8080);
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    
    sendto(sock,&hel,sizeof(int),MSG_CONFIRM,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    printf("Number sent\n");

    //close(new_socket);
    return 0;
}
