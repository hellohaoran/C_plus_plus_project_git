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
    // setsockopt设置bind;如果在time_wait 时间内重启服务器不会阻塞
    int ret_= setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)); 
    ERROR_CHECK(ret_, -1 ,"setsockopt"); 
    int ret  =  bind(sockFd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret , -1 , "bind");
    // 监听半连接队列的对象 socket
    ret = listen(sockFd,10); 
    ERROR_CHECK(ret , -1 , "listen");
    // accept 本质是读操作: 有连接时 就绪 ; 没连接时阻塞
    int netFd =  accept(sockFd, NULL,NULL ); 
    // 原则是哪个文件描述符需要异步访问,哪个就加入集合
    char buf[1024] = {0};
    bzero(buf, sizeof(buf));
    // 只从缓冲区复制 ; 不从缓冲区取出
     ret = recv(netFd , buf , sizeof(buf), MSG_PEEK) ;
    ERROR_CHECK(ret , -1 , "recv") ;
    puts(buf);
    bzero(buf , sizeof(buf));
    ret = recv(netFd, buf , sizeof(buf) , 0 );
    ERROR_CHECK(ret , -1 , "recv") ;
    puts(buf);

 

    close(netFd);

    close(sockFd); 
}