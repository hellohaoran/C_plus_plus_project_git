#include<c43func.h>
int main(int argc, char*argv[]){
    // ./server 本地IP地址 端口号 
    // 创建一个socket,支持IPV4, TCP
    int sockFd = socket(AF_INET, SOCK_STREAM, 0); 
    ERROR_CHECK(sockFd, -1 , "socket");
    printf("sockFd = %d\n", sockFd) ; 
    struct sockaddr_in addr; // 用
    addr.sin_port = htons(atoi(argv[2])); // 端口转换成网络字节序(大端)
    addr.sin_family = AF_INET ;
    addr.sin_addr.s_addr = inet_addr(argv[1]); 
    // sizeof 不用 strlen  地址的大小; ( struct sockaddr * ) addr 转换成sockaddr 地址
    // int ret = connect(sockFd,( struct sockaddr * )&addr,sizeof(addr));  
    //对于bind而言, 先取地址再强转; 
    int ret = bind(sockFd,(struct sockaddr*)&addr,sizeof(addr)); 
    ERROR_CHECK(ret , -1 , "bind"); 
    ret = listen(sockFd, 10);
    ERROR_CHECK(ret , -1 , "listen");
    // 以下是获取对方的IP地址和端口的accept的写法
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr) ; 
    int netFd = accept(sockFd,(struct sockaddr*)&client_addr, &client_addrlen); 
    ERROR_CHECK(netFd, -1 , "accept");
    printf("netFd = %d\n", netFd); 
    printf("client ip = %s\n", inet_ntoa(client_addr.sin_addr) );
    printf("client port = %d\n", ntohs(client_addr.sin_port));
    printf("client family = %d\n", client_addr.sin_family);
    printf("client addrlen = %d\n", client_addrlen);
    // send(netFd, "hello from server", 17,0);
    // char buf[4096] = {0};
    // recv(netFd,buf,sizeof(buf), 0);
    // puts(buf);
    
     send(netFd, "how are you from client", strlen("how are you from client"), 0); 
    send(netFd, "ok I am folensd", strlen("ok I am folensd"), 0);
    send(netFd, "wosdasdaf", strlen("wosdasdaf"), 0);
    
    printf("sizeof = %ld", sizeof("how are you from clienthow are you I am fine"));
    printf("strlen = %ld", strlen("how are you from clienthow are you I am fine"));
   
    close(netFd); 
    // sleep(60);
    close(sockFd); 
}