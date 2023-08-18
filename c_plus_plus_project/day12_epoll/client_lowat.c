#include<c43func.h>
int main(int argc,char *argv[]){
      // ./client_lowat 192.168.77.129 1234
    // ./server  192.168.77.129 1234
    // socket connect select send recv
    ARGS_CHECK(argc,3); 
    //读网络->recv会阻塞; 读标准输入会阻塞
    int sockFd = socket(AF_INET, SOCK_STREAM, 0); 
    // struct sockaddr_in 在man 7 ip 
    struct sockaddr_in addr ;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_family = AF_INET; 
    int ret = connect(sockFd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret , -1 , "connect");
    char buf[1024] = {0};
    // 原则是哪个文件描述符需要异步访问,哪个就加入集合
    fd_set rdset; 
    while(1){
        // 从键盘输入数据之后\n就已经输入到缓冲, 这时输入缓冲区就绪
    FD_ZERO(&rdset);
    FD_SET(sockFd, &rdset);
    FD_SET(STDIN_FILENO, &rdset);
    select(sockFd+1, &rdset,NULL,NULL,NULL);
    if(FD_ISSET(STDIN_FILENO,&rdset)){
        bzero(buf,sizeof(buf));
        int ret_= read(STDIN_FILENO, buf, sizeof(buf));
        if(ret_ == 0){
            puts("client over!\n");
            break;
        }
        //再将读到buf里面的有效数据输到网络中所以不能用sizeof; 
        send(sockFd, buf,strlen(buf),0);
    }
    //读端关闭  
    if(FD_ISSET(sockFd, &rdset)){ 
        bzero(buf, sizeof(buf)); 
        // 收到数剧超过5个字节才 展示
        int lowat = 5;
        setsockopt(sockFd , SOL_SOCKET , SO_RCVLOWAT , &lowat , sizeof(lowat)) ;

        int ret = recv(sockFd, buf,sizeof(buf),0) ;
        if(ret == 0){
            puts("chat is end!");
            break; 
        }
        puts(buf); 

    }

    }
    close(sockFd);


    

}