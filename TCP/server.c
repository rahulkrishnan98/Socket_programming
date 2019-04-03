
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
    int sockfd, newsockfd;
    sockfd=socket(AF_INET, SOCK_STREAM,0);
    int clientlen;
    bzero((char*)&server, sizeof(server));
    inet_aton("127.0.0.1",&server.sin_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(3000);

    bind(sockfd,(struct sockaddr*)&server, sizeof(server));
    listen(sockfd,5);
    char msg[50];
    for(;;){
        newsockfd=accept(sockfd,(struct sockaddr*)&client,&clientlen);
        int childpid=fork();
        if(childpid==0){
            close(sockfd);
            read(newsockfd,msg,50);
            for(int i=0;msg[i]!='\0';i++){
                msg[i]=toupper(msg[i]);
            }
            write(newsockfd, msg, 50);
            printf("Writtent to newsockfd");
            exit(0);
        }
        else{
            printf("Didnt enter the child");
        }
        close(newsockfd);
    }
    return 0;


}