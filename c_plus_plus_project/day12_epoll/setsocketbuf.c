#include<c43func.h>
int main(){
     // socket 的设置;
     int bufsize;
      //  getsockopt 里面设置 SO_SNDBUF 属性 ;关于socket属性在 man 7 socket 里面设置 ;
     socklen_t len  = sizeof(bufsize);
     int sockFd = socket(AF_INET  , SOCK_STREAM , 0) ;
     int ret = getsockopt(sockFd,SOL_SOCKET ,SO_SNDBUF , &bufsize , &len) ;
     ERROR_CHECK(ret , -1 , "getsockFd") ;
     printf("bufsize = %d , len = %d\n" , bufsize , len );
     bufsize = 4096 ; // 设置 缓冲区大小
     ret = setsockopt(sockFd , SOL_SOCKET ,SO_SNDBUF,&bufsize , len) ;
     ERROR_CHECK(ret , -1 , "setsockopt") ;
     ret = getsockopt(sockFd , SOL_SOCKET , SO_SNDBUF , &bufsize , &len);
     printf("bufsize = %d , len = %d\n" , bufsize , len );

}