#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    int sock=0,client_fd,new_socket,valread;
    struct sockaddr_in serv_addr;
    int addrlen = sizeof(serv_addr);
    float hel=5.0;

    //Creation socket file descriptor
    if ((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket failed");
        return 0;
    }
    printf("Socket Created\n");
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(8080);
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    //Connect server
    if ((client_fd=connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))<0)
    {
        perror("connect failed");
        return 0;
    }
    printf("Connected\n");
    send(sock,&hel,sizeof(float),0);
    printf("Float sent\n");

    //close(new_socket);
    return 0;
}
