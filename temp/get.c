#include <stdio.h>
#include <sys/socket.h>//connect, sockaddr, etc.
#include <unistd.h>//for close()
#include <string.h>//memset, memcpy
#include <netdb.h>//hostent,gethostbyname, etc.

int main(void){

    const char *target_host = "www.google.co.jp"; 
    const char *target_uri = "/";
    const int target_port = 80;

    int sofd = socket(AF_INET,SOCK_STREAM,0);

    struct hostent *shost;
    shost = gethostbyname(target_host);

    struct sockaddr_in sv_addr;
    memset(&sv_addr,'\0',sizeof(sv_addr));
    sv_addr.sin_family = AF_INET;
    sv_addr.sin_port = htons(target_port);
    memcpy((char*)&sv_addr.sin_addr,(char *)shost->h_addr,shost->h_length);

    connect(sofd,(const struct sockaddr*)&sv_addr,sizeof(sv_addr));

    send(sofd,"GET ",strlen("GET "),0);
    send(sofd,target_uri,strlen(target_uri),0);
    send(sofd," HTTP/1.0",strlen(" HTTP/1.0"),0);
    send(sofd,"\r\n",strlen("\r\n"),0);
    send(sofd,"Host: ",strlen("Host: "),0);
    send(sofd,target_host,strlen(target_host),0);
    send(sofd,"\r\n",strlen("\r\n"),0);
    send(sofd,"\r\n",strlen("\r\n"),0);

    char http_res[1024];
    while(recv(sofd,http_res,sizeof(http_res),0)){
        printf("%s",http_res);
        memset(&http_res,'\0',sizeof(http_res));
    }

    close(sofd);

    return 0;
}


