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
    float buf;
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
    int len;
    sendto(sock,0,0,MSG_CONFIRM,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    valread=recvfrom(sock,&buf,sizeof(float),MSG_WAITALL,(struct sockaddr*)&serv_addr,&len);
    printf("Increased Float :%.2f\n",buf);

    //close(new_socket);
    return 0;
}
