#include <c43func.h>
// 具有断线重连的功能;
int main(int argc, char *argv[])
{
    // ./client 192.168.77.129 1234
    // ./server_v3  192.168.77.129 1234
    // socket connect select send recv

    ARGS_CHECK(argc, 3);
    // 读网络->recv会阻塞; 读标准输入会阻塞
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    // struct sockaddr_in 在man 7 ip
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_family = AF_INET;
    int optval = 1;
    int ret_ = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
    ERROR_CHECK(ret_, -1, "setsockopt");
    int ret = bind(sockFd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");
    // 监听半连接队列的对象 socket
    ret = listen(sockFd, 10);
    ERROR_CHECK(ret, -1, "listen");
    // 放置 netFd的集合: 用于 读写缓冲区
    int netFdArr[10];
    // 创建epfd 初始化监听集合
    int epFd = epoll_create(1);
    struct epoll_event event;
    event.data.fd = sockFd;
    event.events = EPOLLIN;
    // 设置监听集合
    epoll_ctl(epFd, EPOLL_CTL_ADD, sockFd, &event);
    // 设置就绪集合
    char buf[4096] = {0};
    struct epoll_event readyArr[11] = {0};
    int curConn = 0;
    // 实现聊天室
    // 服务端不再监听标准输入
    //  服务端功能不再监听标准输入, 服务端处理新的客户端连入(监听sockFd),
    // 处理客户端发送的消息的转发:维护netFd的数组然后进行转发
    while (1)
    {
        // 设置就绪集合
        int readyNum = epoll_wait(epFd, readyArr, 11, 0);
        // 两种就绪 : 1.客户端建立连接的就绪 ;2 . 客户端发数据的就绪
        for (int i = 0; i < readyNum; ++i)
        {
            if (readyArr[i].data.fd == sockFd)
            {
                // 接收到
                netFdArr[curConn] = accept(sockFd, NULL, NULL);
                // 加入监听
                puts("new connect has builded");
                event.data.fd = netFdArr[curConn];
                event.events = EPOLLIN;
                epoll_ctl(epFd, EPOLL_CTL_ADD, netFdArr[curConn], &event);
                // 当前的数量加1; netFd 已连接的描述符加1;
                printf("now new connect is arrive curcnt = %d \n", curConn);
                curConn++; 

            }
            //就绪队列里的netFd读就绪;
          else{
                // 获得 ; 
                bzero(buf , sizeof(buf));
                int ret = recv(readyArr[i].data.fd,buf , sizeof(buf), 0);
                if(ret == 0){
                    sprintf(buf, "%d已挂断\n",i);
                    close(readyArr[i].data.fd);
                }
                for(int j = 0; j<curConn ; ++j){
                    if(netFdArr[j] == readyArr[i].data.fd){
                        // 如果 两个描述符相等;
                        continue;
                    }
                    send(netFdArr[j],buf,sizeof(buf), 0);
                }

            }
        }
    }
    close(sockFd);

}
// close(netFd);
