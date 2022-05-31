#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    int server_fd,server_bd,new_socket1,new_socket2,valread,listserv;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int buf;

    //Creation socket file descriptor
    if ((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("socket failed");
        return 0;
    }
    printf("Socket Created\n");
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(8080);
    //Bind address to socket
    if (bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0)
    {
        perror("bind failed");
        return 0;
    }
    printf("Binded\n");
    //Listen
    if (listen(server_fd,3)<0)
    {
        perror("listen");
        return 0;
    }
    printf("Listening\n");
    //Accept client
    if ((new_socket1=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0)
    {
        perror("accept");
        return 0;
    }
    printf("Accepted Client1\n");
    valread=read(new_socket1,&buf,sizeof(int));
    printf("Number Received :%d\n",buf);
    if ((new_socket2=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0)
    {
        perror("accept");
        return 0;
    }
    printf("Accepted Client2\n");
    int sq=buf*buf;
    send(new_socket2,&sq,sizeof(int),0);
    printf("Squared Number Sent\n");

    //close(new_socket);
    //shutdown(server_fd,SHUT_RDWR);
    return 0;
}

