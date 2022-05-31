#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    int server_fd,server_bd,len1,len2,valread,listserv;
    struct sockaddr_in address,cliaddr1,cliaddr2;
    int addrlen = sizeof(address);
    char buffer[1024]={0};

    //Creation socket file descriptor
    if ((server_fd=socket(AF_INET,SOCK_DGRAM,0))==0)
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
    len1=sizeof(cliaddr1);
    len2=sizeof(cliaddr2);
    valread=recvfrom(server_fd,buffer,1024,MSG_WAITALL,(struct sockaddr*)&cliaddr1,&len1);
    printf("%s\n",buffer);
    int i,j,temp;
    int l=strlen(buffer);
    for (i = 0, j = l-1; i < j; i++, j--)
    {
        temp=buffer[j];
        buffer[j]=buffer[i];
        buffer[i]=temp;
    }
    recvfrom(server_fd,0,0,MSG_WAITALL,(struct sockaddr*)&cliaddr2,&len2);
    sendto(server_fd,buffer,strlen(buffer),MSG_CONFIRM,(struct sockaddr*)&cliaddr2,len2);
    printf("Reverse String Sent\n");

    //close(new_socket);
    //shutdown(server_fd,SHUT_RDWR);
    return 0;
}

