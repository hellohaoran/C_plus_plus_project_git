#include<c43func.h>
int setNonblcok(int fd){
    int status = fcntl(fd ,F_GETFL) ; // 获取文件描述符的状态
    // 原来的属性加上O_NONBLOCK (非阻塞)
    status |= O_NONBLOCK ;
    //将fd设置属性
    int ret = fcntl(fd , F_SETFL , status) ; 
    ERROR_CHECK(ret , -1 ,"fcnl");
    return 0 ; 

}
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
    socklen_t addrlen = sizeof(addr) ;
    int netFd =  accept(sockFd, (struct sockaddr *) &addr, &addrlen); 
    // 原则是哪个文件描述符需要异步访问,哪个就加入集合
    printf("ip = %s\n",inet_ntoa(addr.sin_addr));
    printf("port = %d\n",ntohs(addr.sin_port));
    printf("addr family = %d\n",addr.sin_family);
    char buf[1024] = {0};
    //  setNonblcok(netFd) ;
     //因为改变了文件描述符:netfd 所以recv的返回值发生变化; 这个是临时发生了变化, 也是改变了netFd的文件属性;
    int  res = recv(netFd,buf , sizeof(buf),MSG_DONTWAIT)  ;

    // ERROR_CHECK(res , -1,"recv"); 
    if(res == -1){ // 阻塞返回值是-1 有: 没有数据
        puts("no resourse now");
    }
    res = recv(netFd,buf , sizeof(buf),0);
    // 以下是同步非阻塞
    // int res ; 
    // while(1){
    //     // 临时recv非阻塞
    //  res = recv(netFd , buf,sizeof(buf), MSG_DONTWAIT) ; 
    // if(res == -1 ){
    //     puts("no resource now");
    // }
    // else{
    //     break;
    // }
    // }
    puts(buf);

    


}