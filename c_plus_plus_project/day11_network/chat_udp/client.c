#include<c43func.h>
int main(int argc, char*argv[]){
    // udp 会保留消息的边界; tcp不会
    ARGS_CHECK(argc, 3);
    int sockFd = socket(AF_INET,SOCK_DGRAM , 0);
    ERROR_CHECK(sockFd ,-1, "socket");
    struct sockaddr_in addr;
    addr.sin_addr.s_addr =inet_addr(argv[1]);
    addr.sin_family = AF_INET ;
    addr.sin_port = htons(atoi(argv[2])) ;
    char buf[1024] = "hello udp\n"; 
    int ret = sendto(sockFd, buf, strlen(buf), 0, (struct sockaddr* ) &addr, sizeof(addr));
    bzero(buf, sizeof(buf));
    socklen_t addrlen = sizeof(addr); 
    recvfrom(sockFd,buf,sizeof(buf), 0, (struct sockaddr*) &addr, &addrlen);
    printf("msg from server  %s\n", buf);
    

    close(sockFd);
}