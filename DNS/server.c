#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    struct sockaddr_in server;
    struct sockaddr_in client;

    unsigned int sockfd;
    sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    bzero((char*)&server, sizeof(server));

    inet_aton("127.0.0.1",&server.sin_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(3000);

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    
    char rmsg[256];
    unsigned int clientlen;
    recvfrom(sockfd, rmsg,100,0,(struct sockaddr*)&client, clientlen);
    printf("Message received from client %s\n",rmsg);
    
    //ip translation
    FILE* fileptr=fopen("dns.txt","r");
    if(fileptr==NULL){
        printf("Cannot open lookup, error");
        exit(0);
    }
    char line[200];
    char msg[100];
    while(fgets(line,sizeof(line),fileptr)){
        char *s=strtok(line,",");
        while(s!=NULL){
            if(strcmp(rmsg,s)==0){
                s=strtok(NULL,",");
                for(int j=0;s[j]!='\0';j++){
                    msg[j]=s[j];
                }
                break;
            }
            else{
                s=strtok(NULL,",");
            }
        }
    }
    
    printf("%s\n",msg);
    sendto(sockfd, msg, 100, 0, (struct sockaddr*)&client, clientlen);
    return 1;
}