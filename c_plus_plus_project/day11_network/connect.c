#include<c43func.h>
int main(int argc, char*argv[]){
    // ./connect 目的IP地址 端口号 
    // 创建一个socket,支持IPV4, TCP
    int sockFd = socket(AF_INET, SOCK_STREAM, 0); 
    ERROR_CHECK(sockFd, -1 , "socket");
    printf("sockFd = %d\n", sockFd) ; 
    struct sockaddr_in addr;
    addr.sin_port = htons(atoi(argv[2])); // 端口转换成网络字节序(大端)
    addr.sin_family = AF_INET ;
    addr.sin_addr.s_addr = inet_addr(argv[1]); 
    // sizeof 不用 strlen  地址的大小; ( struct sockaddr * ) 转换成地址
    int ret = connect(sockFd,( struct sockaddr * )&addr,sizeof(addr));  
    ERROR_CHECK(ret , -1 , "connect"); 
    char buf[4096] =  {0};
     recv(sockFd, buf,sizeof(buf), 0);
    puts(buf);
//    recv(sockFd, buf,sizeof(buf), 0);
//     puts(buf);

    close(sockFd); 
}