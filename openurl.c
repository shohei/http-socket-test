#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "openurl.h"
#include <string.h>

typedef int bool;
#define TRUE  1
#define FALSE 0

static int sofd;
static struct hostent     *shost;
static struct sockaddr_in sv_addr;

int openurl (char *output_filename, char* target_host, char* target_uri, int target_portno){

    char http_res[1024];

    if (target_portno < 0 || target_portno > 65536) {
        fprintf(stderr, "PORT_NO of httpd server is invalid\n");
        return -1;
    }

    sofd = socket(AF_INET, SOCK_STREAM, 0);
    if (sofd < 0) {
        fprintf(stderr, "can not open SOCKET.\n");
        return 1;
    }

    shost = gethostbyname(target_host);
    if (shost == NULL) {
        fprintf(stderr, "err happend in gethostbyname function.\n");
        return 1;
    }

    memset(&sv_addr, '\0', sizeof(sv_addr));
    sv_addr.sin_family = AF_INET;
    sv_addr.sin_port   = htons(target_portno);
    memcpy((char *)&sv_addr.sin_addr, (char *)shost->h_addr, shost->h_length);

    if (connect(sofd,(const struct sockaddr*)&sv_addr, sizeof(sv_addr)) < 0) {
        fprintf(stderr, "err happend in connect function.\n");
        return 1;
    }

    send(sofd, "GET ",      strlen("GET "),      0);
    send(sofd, target_uri,  strlen(target_uri),  0);
    send(sofd, " HTTP/1.0", strlen(" HTTP/1.0"), 0);
    send(sofd, "\r\n",      strlen("\r\n"),      0);
    send(sofd, "Host: ",    strlen("Host: "),    0);
    send(sofd, target_host, strlen(target_host), 0);
    send(sofd, "\r\n",      strlen("\r\n"),      0);
    send(sofd, "\r\n",      strlen("\r\n"),      0);

    bool onErrorRemove = remove(output_filename); 
    if(onErrorRemove==FALSE){
       printf( "%s removed.\n", output_filename );
    }
    else{
      printf( "%s: no such file.\n",output_filename);
      fprintf(stderr,"%d",onErrorRemove);
    }

    FILE *fp;
    fp = fopen(output_filename,"w");
    if(fp==NULL){
        fprintf(stderr,"cannot open output file\n");
        return 1;
    }

    bool isHeader = TRUE;
    while (recv(sofd, http_res, sizeof(http_res), 0)) {
        if(isHeader){
            char c1, c2, c3, c4;
            int i;
            for(i=0;i<strlen(http_res);i++){
                c1 = http_res[i];
                c2 = http_res[i+1];
                c3 = http_res[i+2];
                c4 = http_res[i+3];
                if(c1=='\r' && c2=='\n' && c3=='\r' && c4=='\n'){
                    printf("break at %d\n",i);
                    break;
                }
            };
            printf("sliced: %d\n",i);
            char *html;
            html = &http_res[i+4];//remove line ending 
            /* printf(html); */
            fprintf(fp,"%s",html);
            isHeader = FALSE;
        }
        else {
            /* printf("%s",http_res); */
            fprintf(fp,"%s",http_res);
            memset(&http_res, '\0', sizeof(http_res));
        }
    }
    fclose(fp);

    close(sofd);

    return 0;
}

