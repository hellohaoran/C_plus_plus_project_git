#include<c43func.h>
int main(int argc,char *argv[]){
      // ./client 192.168.77.129 1234
    // 水平触发; 多次就绪的例子;
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
    int epFd = epoll_create(1) ; //  创建epoll文件对象 这个参数只要正数; 没什么用
    struct epoll_event event ;
    event.data.fd = STDIN_FILENO ; // 事件的描述符;
    event.events = EPOLLIN ; // 事件的类型是EPOLLIN; 
    // 加入监听集合
    epoll_ctl(epFd , EPOLL_CTL_ADD, STDIN_FILENO , & event);
    event.data.fd =   netFd ; // 监视的文件描述符 
    // 监视的事件的类型; 将netFd 以读事件加入监听 netFd 以边缘触发的形式
    event.events = EPOLLIN | EPOLLET; 
    // 加入监听集合
    epoll_ctl(epFd , EPOLL_CTL_ADD, netFd , &event);
    char buf[4] = {0};
    struct epoll_event readyArr[2] ;  // 就绪事件的结合
    while(1){
        int readyNum = epoll_wait(epFd, readyArr , 2, -1) ;// 阻塞不限时间 这时epoll_wait如果有就绪就会将就绪事件加入集合    
        puts("epoll_wait has returned") ;
        for(int i =0; i < readyNum ;  ++i){
            if(readyArr[i].data.fd == STDIN_FILENO){
                bzero(buf, sizeof(buf));
                int ret = read(STDIN_FILENO , buf , sizeof(buf));
                if(ret == 0){
                    goto end;
                }
                send(netFd, buf, strlen(buf) , 0);
            }
            else if(readyArr[i].data.fd == netFd){
                
                int ret;
                //while+ 非阻塞 读取 ; 
                while(1){
                    bzero(buf , sizeof(buf));
                    ret = recv(netFd , buf , sizeof(buf) , MSG_DONTWAIT);
                    puts(buf);
                    if(ret == 0|| ret == -1){
                        break;
                    }
                }
                
            }
        }
    }
    end:
    close(netFd);
    close(epFd);
    close(sockFd); 
}