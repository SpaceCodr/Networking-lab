#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

int buffer[3];
int array[10];
void findval();

int main(int argc, char const *argv[])
{
    int server_fd,server_bd,new_socket,valread,listserv;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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
    valread=read(new_socket,&array,10*sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n",array[i]);
    }

    findval();

    send(new_socket,&buffer,3*sizeof(int),0);
    printf("Results sent\n");

    //close(new_socket);
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