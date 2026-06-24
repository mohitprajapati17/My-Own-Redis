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
    
    
    return 0;
}