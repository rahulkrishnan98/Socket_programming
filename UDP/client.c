#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
    struct sockaddr_in server;
    struct sockaddr_in client;
    unsigned int client_len;

    unsigned int sockfd;
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    
//server details
    bzero((char*)&server, sizeof(server));
    inet_aton("127.0.0.1",&server.sin_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(3000);
 //client details
    bzero((char*)&client, sizeof(client));
    inet_aton("127.0.0.1",&client.sin_addr);
    client.sin_family=AF_INET;
    client.sin_port=htons(0);

    bind(sockfd, (struct sockaddr*)&client, sizeof(client));

    char msg[100]="Hi I want all caps";
    sendto(sockfd, msg,100,0,(struct sockaddr*)&server, sizeof(server));
    recvfrom(sockfd, msg, 100, 0, (struct sockaddr*)&client, &client_len);
    printf("%s",msg);
    return 0;
}