#include<c43func.h>
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);
    int sockFd = socket(AF_INET , SOCK_DGRAM , 0);
    ERROR_CHECK(sockFd, -1,"socket");
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_family = AF_INET ;
    addr.sin_port = htons(atoi(argv[2]));
    socklen_t addrlen = sizeof(addr); 
    sendto(sockFd,"我是客户端",strlen("我是客户端"),0,(struct sockaddr *)&addr, sizeof(addr) );
    fd_set rdset;
    char buf[1024] = {0};
    while(1){  
        FD_ZERO(&rdset);
        FD_SET(sockFd,&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        select(sockFd+1, &rdset,NULL,NULL,NULL);
        if(FD_ISSET(sockFd,&rdset)){
            bzero(buf, sizeof(buf)); 
            int ret = recvfrom(sockFd,buf,sizeof(buf), 0,(struct sockaddr*)&addr , &addrlen);
            if(ret == 0){
                // 如果返回值为 0 
                puts("chat end!");
                break;
            }
            puts(buf);

        }
        if(FD_ISSET(STDIN_FILENO, &rdset)){
            bzero(buf,sizeof(buf));
            int ret_ = read(STDIN_FILENO, buf, sizeof(buf));
            if(ret_ == 0){
                puts("chat end!");
                // 与tcp不同的是 udp发个0字节的报文 对方recvfrom会返回 0 
                sendto(sockFd, buf,0,0,(struct sockaddr*)&addr, addrlen);
                break;
            }
           sendto(sockFd, buf, strlen(buf), 0, (struct sockaddr *)&addr, addrlen); 
        }

    }
}