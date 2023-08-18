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
    socklen_t addrlen = sizeof(addr);
    // accept 本质是读操作: 有连接时 就绪 ; 没连接时阻塞

    char buf[1024] = {0};
    // 原则是哪个文件描述符需要异步访问,哪个就加入集合
    fd_set rdset, monitor; // 分成就绪事件的集合和监听集合
    // monitor是监听集合
    // rdset是就绪集合
    // accept 放在select后面,
    // 去使用时确保从标准输入中输入数据在客户端建立连接之后
    // 每次accept后都要创建新的netFd, netFd加入监听----> 分离监听和就绪
    // 客户端如果断开连接后 ,服务端不退出, 取消监听netFd

    FD_ZERO(&rdset);
    FD_ZERO(&monitor);
    FD_SET(sockFd, &monitor); // 将sockFd->全连接有连接的话 sockFd 读就绪->accept就绪, 加入monitor
    FD_SET(STDIN_FILENO, &monitor);
    int netFd[20] = {0};
    int curr = 0;
    //实现聊天室
    //服务端不再监听标准输入
    // 服务端功能不再监听标准输入, 服务端处理新的客户端连入(监听sockFd), 
    //处理客户端发送的消息的转发:维护netFd的数组然后进行转发
    while (1)
    {
        // 从键盘输入数据之后\n就已经输入到缓冲, 这时输入缓冲区就绪
        memcpy(&rdset, &monitor, sizeof(monitor)); // 拷贝到rdset中;
        select(20, &rdset, NULL, NULL, NULL);      // 因为监听集合的描述符最大值很难找所以填一个20

        if (FD_ISSET(sockFd, &rdset))
        {
            // 新链接一到就将sockFd加入到monitor中

            netFd[curr] = accept(sockFd, (struct sockaddr *)&addr, &addrlen);
            FD_SET(netFd[curr], &monitor); // 新链接到来monitor就要扩容
            curr++;
            puts("new connect is accepted\n");
        }
        // 两种就绪 : 1.客户端建立连接的就绪 ;2 . 客户端发数据的就绪
        for (int i = 0; i < curr; ++i)
        {
            if (FD_ISSET(netFd[i], &rdset))
            {
                // 读就绪
                bzero(buf, sizeof(buf));
                int ret = recv(netFd[i], buf, sizeof(buf), 0);
                if (ret == 0) // 如果是
                {
                    // ret == 0
                    sprintf(buf,"第%d号已下线", i);
                    FD_CLR(netFd[i], &monitor);
                    close(netFd[i]);
                }
                for (int j = 0; j < curr; ++j)
                {
                    if (j == i)
                    {
                        continue;
                    }
                    send(netFd[j], buf, sizeof(buf), 0);
                }
            }
        }
    }
    close(sockFd);
}
// close(netFd);
