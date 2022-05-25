#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    int server_fd,server_bd,new_socket,valread,listserv;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024]={0};
    char* hello="Hello from server";

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
    if ((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0)
    {
        perror("accept");
        return 0;
    }
    printf("Accepted\n");
    valread=read(new_socket,buffer,1024);
    printf("%s\n",buffer);
    send(new_socket,hello,strlen(hello),0);
    printf("Hello message sent\n");

    //close(new_socket);
    //shutdown(server_fd,SHUT_RDWR);
    return 0;
}

