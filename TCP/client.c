
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    int sockfd;
    sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    struct sockaddr_in server;
    struct sockaddr_in client;

    bzero((char*)&server, sizeof(server));
    inet_aton("127.0.0.1",&server.sin_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(3000);
    
    connect(sockfd,(struct sockaddr*)&server, sizeof(server));
    char data[50]="Hey";
    write(sockfd,data,50);
    read(sockfd, data, 50);
    printf("%s\n",data);
    close(sockfd);
    exit(0);
    return 0;
}