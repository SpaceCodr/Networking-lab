#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include <sys/types.h>

int buffer[3];
int array[10];
void findval();

int main()
{
    int sockfd,len,valread;
    struct sockaddr_in address,cliaddr;
    int addrlen = sizeof(address);

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
    valread=recvfrom(sockfd,(char *)array,10*sizeof(int),MSG_WAITALL,(struct sockaddr*)&cliaddr,&len);
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n",array[i]);
    }
    findval();
    sendto(sockfd,(const char *)buffer,3*sizeof(int),MSG_CONFIRM,(struct sockaddr*)&cliaddr,len);
    printf("Result sent\n");
    //shutdown(server_fd,SHUT_RDWR);
    return 0;
}

void findval(){
    int temp1=array[0];
    int temp2=array[0];
    buffer[2]=array[0];
    buffer[0]=temp1;
    buffer[1]=temp2;
    for (int i = 1; i < 10; i++)
    {
        if (array[i]<temp2)
        {
            temp2=array[i];
            buffer[1]=temp2;
        }
        else if (array[i]>temp1)
        {
            temp1=array[i];
            buffer[0]=temp1;
        }
        buffer[2]+=array[i];    
    }
    buffer[2]/=10;
}