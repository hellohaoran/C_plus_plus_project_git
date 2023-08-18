#include<c43func.h>
int main(int argc ,char* argv[]){
    ARGS_CHECK(argc , 3 );
    int sockFd = socket(AF_INET , SOCK_DGRAM ,  0 );
    struct sockaddr_in addr; 
    addr.sin_family = AF_INET ; 
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    int ret = bind(sockFd,(struct sockaddr*) &addr, sizeof(addr));
    ERROR_CHECK(ret , -1 ,"bind");
    //以下是用来保存对端的地址 这样服务器可以发送数据给对端
    struct sockaddr_in client_addr ;
    socklen_t client_addrlen = sizeof(client_addr); 
    char buf[1024] = {0}; 
    recvfrom(sockFd,buf, sizeof(buf), 0,    (struct sockaddr*) &client_addr, &client_addrlen); 
    
    sendto(sockFd,"I am fine thank you!", strlen("I am fine thank you!"), 0,(struct sockaddr *)&client_addr,sizeof(client_addr) );
    
    printf("buf = %s",buf);
    printf("client ip = %s\n", inet_ntoa(client_addr.sin_addr));
    printf("client port = %d\n", ntohs(client_addr.sin_port));
    close(sockFd); 

}