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
    int sockfd;
    int buffer[3];
    int array[10]={4,5,6,3,2,7,11,23,32,10};
    struct sockaddr_in servaddr;

    //Creation socket file descriptor
    if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket failed");
        return 0;
    }
    printf("Socket Created\n");

    //memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8080);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    int len,n;
    sendto(sockfd, (const char *)array,10*sizeof(int),MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
	printf("Array sent.\n");		
	n = recvfrom(sockfd, (int *)buffer,3*sizeof(int),MSG_WAITALL, (struct sockaddr *) &servaddr,&len);
	for (int i = 0; i < 3; i++)
    {
        printf("%d\n",buffer[i]);
    }
	close(sockfd);
	return 0;
}