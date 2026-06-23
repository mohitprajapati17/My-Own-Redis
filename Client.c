#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

static void die(const char *msg){
    int err=errno;
    fprintf(stderr,"[%d] %s \n",err,msg);
    abort();

}