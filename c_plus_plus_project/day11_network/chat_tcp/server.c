#include<c43func.h>
int main(int argc,char *argv[]){
      // ./client 192.168.77.129 1234
    // ./server_v3  192.168.77.129 1234
    // socket connect select send recv


    ARGS_CHECK(argc,3); 
    //读网络->recv会阻塞; 读标准输入会阻塞
    int sockFd = socket(AF_INET, SOCK_STREAM, 0); 
    // struct sockaddr_in 在man 7 ip 
    struct sockaddr_in addr ;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_family = AF_INET ; 
    int optval = 1;
    int ret_= setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)); 
    ERROR_CHECK(ret_, -1 ,"setsockopt"); 
    int ret =  bind(sockFd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret , -1 , "bind");
    // 监听半连接队列的对象 socket
    ret = listen(sockFd,10); 
    ERROR_CHECK(ret , -1 , "listen");
    socklen_t  addrlen = sizeof(addr);  
    // accept 本质是读操作: 有连接时 就绪 ; 没连接时阻塞
    int netFd =  accept(sockFd, (struct sockaddr*) &addr , &addrlen ) ; 
    char buf[1024] = {0};
    // 原则是哪个文件描述符需要异步访问,哪个就加入集合
    fd_set rdset ;// 分成就绪事件的集合和监听集合
    // monitor是监听集合
    // rdset是就绪集合


    while(1){
        // 从键盘输入数据之后\n就已经输入到缓冲, 这时输入缓冲区就绪
    FD_ZERO(&rdset); 
    FD_SET(netFd, &rdset);
    FD_SET(STDIN_FILENO, &rdset);
    select(netFd+1, &rdset,NULL,NULL,NULL);
    if(FD_ISSET(STDIN_FILENO,&rdset)){
        bzero(buf,sizeof(buf));
        int ret_ = read(STDIN_FILENO, buf, sizeof(buf));
        //再将读到buf里面的有效数据输到网络中所以不能用sizeof; 
        if(ret_ == 0){
            puts("server over!\n");
        }
        send(netFd, buf,strlen(buf),0);
    }
    if(FD_ISSET(netFd, &rdset)){

        bzero(buf, sizeof(buf)); 
        int ret = recv(netFd, buf,sizeof(buf),0) ;
        if(ret == 0){
            puts("chat is end!");
            break; 
        }
        puts(buf); 
    }
    }
    close(netFd);
    close(sockFd);


    

}