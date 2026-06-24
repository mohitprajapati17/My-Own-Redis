#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>


static void msg(const char *msg){
    fprintf(stderr,"%s\n",msg);
}

static void die(const char* msg){
    int err=errno;
    fprintf(stderr,"[%d] %s\n",err,msg);
    abort();

}

static void do_something (int confd){
     char rbuf[64]={};
     ssize_t n=read(confd , rbuf , sizeof(rbuf)-1);
     if(n<0){
        msg("read() error");
        return ;
     }
     printf(stderr,"Msg from Client: %s\n ", rbuf);

     char ret[]="Hello client";
     write(confd,ret, strlen(ret));
}


int main(){

    int fd=socket(AF_INET , SOCK_STREAM , 0);
    if(fd<0){
        die("socket");
    }

    int val =1;
    setsockopt(fd ,SOL_SOCKET ,SO_REUSEADDR ,&val , sizeof(val));

    struct sockaddr_in addr={};
    addr.sin_family=AF_INET;
    addr.sin_port = ntohs(12345);
    addr.sin_addr.s_addr=ntohl(0);

    int rv=bind(fd , (struct sockaddr *)&addr , sizeof(addr));
    if(rv<0){
        die("bind");
    }

    rv=listen(fd,SOMAXCONN);
    if(rv<0){
        die("listen");
    }

    while(1){
        struct sockaddr_in caddr={};  //address of the client
        socklen_t caddrlen=sizeof(caddr);
        int cfd=accept(fd , (struct sockaddr *)&caddr , &caddrlen);
        if(cfd<0){
            msg("accept error");
            continue;
        }

        do_something(cfd);
        close(cfd);
    }
    

    
    return 0;
}