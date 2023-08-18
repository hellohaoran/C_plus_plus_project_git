#include<c43func.h>
int main(){
    // 创建一个socket,支持IPV4, TCP
    int sockFd = socket(AF_INET, SOCK_STREAM, 0); 
    ERROR_CHECK(sockFd, -1 , "socket");
    printf("sockFd = %d\n", sockFd) ; 
    close(sockFd); 
}