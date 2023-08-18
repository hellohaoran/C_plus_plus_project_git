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
    int netFd = -1; 
    // 原则是哪个文件描述符需要异步访问,哪个就加入集合
    int epFd = epoll_create(1) ; //  创建epoll文件对象 这个参数只要正数; 没什么用
    struct epoll_event event ;
    event.data.fd = STDIN_FILENO ; // 事件的描述符;
    event.events = EPOLLIN ; // 事件的类型是EPOLLIN; 
    // 加入监听集合
    epoll_ctl(epFd , EPOLL_CTL_ADD, STDIN_FILENO , & event);
    event.data.fd =   sockFd ; // 监视的文件描述符 
    event.events = EPOLLIN ; // 监视的事件的类型; 将sockFd 以读事件加入监听
    // 加入监听集合
    epoll_ctl(epFd , EPOLL_CTL_ADD, sockFd , &event);
    char buf[1024] = {0};
    struct epoll_event readyArr[2] ;  // 就绪事件的结合
    int isconnected = 0; // 连接标志;
    time_t check;
    time_t lastMsg; 
    while(1){
        int readyNum = epoll_wait(epFd, readyArr , 3, 1000) ;// 阻塞不限时间 这时epoll_wait如果有就绪就会将就绪事件加入集合    
        puts("epoll_wait has returned") ;
        if(readyNum == 0 && isconnected != 0){
            // 没有在规定时间内发送信息
            // 并且是已连接的状态下; 
            check = time(NULL) ;
            puts("time out!");
            if(check - lastMsg > 5){
                // 如果对端大于5秒未发信息: 就将对端关闭
                send(netFd , "you are free",12,0);
                close(netFd);
                // 将关闭的链接epoll删除监听
                event.data.fd = netFd;
                event.events = EPOLLIN ; //类型是读就绪
                epoll_ctl(epFd, EPOLL_CTL_DEL , netFd, &event);
                isconnected = 0;

            }

        }
        for(int i =0;i<readyNum;i++){
            if(readyArr[i].data.fd == STDIN_FILENO){
                bzero(buf , sizeof(buf));
                int ret = read(STDIN_FILENO , buf, sizeof(buf));
                if(ret == 0){
                    goto end;
                }
                send(netFd, buf, strlen(buf), 0);

            }
            if(readyArr[i].data.fd == sockFd){
                // 有新链接到来
                if(isconnected != 0){
                    // 在有连接的情况下 有新的连接到来;  就关闭这个链接; 
                    int noFd = accept(sockFd , NULL , NULL); 
                    close(noFd);
                    continue; 
                }
                netFd = accept(sockFd , NULL , NULL) ;
                ERROR_CHECK(netFd,-1,"accept");
                puts("new client is coming!") ; 
                //加入epoll监听集合
                event.data.fd = netFd;
                event.events = EPOLLIN ;
                epoll_ctl(epFd , EPOLL_CTL_ADD , netFd , &event); // 将新链接加入epoll监听集合
                isconnected = 1;
                lastMsg = time(NULL); 
            }
            if(readyArr[i].data.fd == netFd){
                // 建立的链接有数据到来
                bzero(buf , sizeof(buf)); 
                int ret = recv(netFd, buf, sizeof(buf) , 0) ;
                if(ret == 0){
                      // 对端关闭链接; 则我们也要关闭链接
                    close(netFd);
                   // 放弃监听这个链接; 
                    event.data.fd = netFd ; 
                    event.events = EPOLLIN ;
                    epoll_ctl(epFd, EPOLL_CTL_DEL , netFd , &event);
                    isconnected = 0;  // 连接标志位置为0; 
                }
                puts(buf);
                lastMsg = time(NULL); 

            }

        }
        }
        end:
            close(sockFd);
            close(netFd);
            close(STDIN_FILENO);

    }
    
