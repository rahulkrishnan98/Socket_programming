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
    struct sockaddr_in server;
    struct sockaddr_in client;

    int sockfd;
    sockfd=socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);

    bzero((char*)&server, sizeof(server));
    inet_aton("127.0.0.1",&server.sin_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(3000);

    connect(sockfd,(struct sockaddr*)&server, sizeof(server));
    char msg[100]="connection requested";
    write(sockfd, msg, 50);
    read(sockfd, msg, 50);
    printf("%s\n",msg);
    close(sockfd);
    exit(0);
    return 0;
}
