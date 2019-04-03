#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>

int main(){
    struct sockaddr_in server;
    struct sockaddr_in client;

    unsigned int sockfd;
    sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    bzero((char*)&server, sizeof(server));
    
/* The inet_aton() function converts the specified string,
in the Internet standard dot notation, 
to a network address, and stores the address in
the structure provided. */
    inet_aton("127.0.0.1",&server.sin_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(3000);

    bind(sockfd,(struct sockaddr*)&server, sizeof(server));

    char rmsg[256];
    
    unsigned int clientlen;
    recvfrom(sockfd,rmsg,100,0,(struct sockaddr*)&client, &clientlen);
    printf("Message received here: %s\n",rmsg);
 
    //convert sentence to all upper case
    char *s= strtok(rmsg," ");
    char msg[100];
    int cnt=0;
    while(s!=NULL){
        printf("%s\n",s);
        
        for(int j=0;s[j]!='\0';j++){
            msg[cnt]=toupper(s[j]);
            cnt++;
        }
        msg[cnt] = ' ';
        cnt++;
        s = strtok(NULL, " ");
    }
    msg[cnt] = '\0';
    printf("%s",msg);
   
    sendto(sockfd,msg,100,0,(struct sockaddr*)&client, clientlen);
    return 1;
}