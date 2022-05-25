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
    char buffer[1024]={0};

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
    if ((new_socket2=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0)
    {
        perror("accept");
        return 0;
    }
    printf("Accepted\n");
    valread=read(new_socket1,buffer,1024);
    printf("%s\n",buffer);
    int i,j,temp;
    int l=strlen(buffer);
    for (i = 0, j = l-1; i < j; i++, j--)
    {
        temp=buffer[j];
        buffer[j]=buffer[i];
        buffer[i]=temp;
    }
    
    send(new_socket2,buffer,strlen(buffer),0);
    printf("Reverse Sent\n");

    //close(new_socket);
    //shutdown(server_fd,SHUT_RDWR);
    return 0;
}

