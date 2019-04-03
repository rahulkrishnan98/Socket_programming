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
    struct sockaddr_in client1,client2;

    int sockfd, newsockfd1, clientlen1;
    int clientlen2,newsockfd2;
    
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    
    inet_aton("127.0.0.1",&server.sin_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(3000);

    //response message
    char resp[100]="You are connected to server";
    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    printf("listening...\n");
    listen(sockfd,5);
    
    //establish two clients
    newsockfd1=accept(sockfd,(struct sockaddr*)&client1, &clientlen1);
    printf("Connected to client1\n");
    write(newsockfd1,resp,100);
    newsockfd2=accept(sockfd,(struct sockaddr*)&client2, &clientlen2);
    printf("Connected to client2");
    write(newsockfd2,resp,100);
}