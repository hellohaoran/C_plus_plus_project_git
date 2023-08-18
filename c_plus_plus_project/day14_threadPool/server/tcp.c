//socekt bind listen
#include<c43func.h>

int tcpInit(int *pSockFd , char * ip, char *port){
    // 是主调函数传进来的可修改的参数
    *pSockFd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(*pSockFd , -1 ,"socket"); 
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip) ;
    int reuse = 1;
    int ret = setsockopt(*pSockFd , SOL_SOCKET , SO_REUSEADDR , &reuse, sizeof(reuse)) ; 
    bind(*pSockFd , (struct sockaddr *) &addr , sizeof(addr));
    ret = listen(*pSockFd,10);
    ERROR_CHECK(ret,-1,"listen" );
    // printf("listen return %d\n", ret);
}