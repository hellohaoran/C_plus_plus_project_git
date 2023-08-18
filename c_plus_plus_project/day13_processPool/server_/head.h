//各种函数的定义
int tcpInit(int *pSockFd , char * ip, char *port); 
int sendFd(int pipeFd , int fdTosend,int exitflag);
int recvFd(int pipeFd , int * pFdToRecv,int * pExitFlag);
int epollAdd(int fd, int epfd) ; // fd加入到epoll监听
int sendFile(int netFd) ; // 发送文件
// 由于有粘包:TCP字节流; 不区分文件名和文件内容; 所以创建自定义的私有协议:
typedef struct train_s{
    int len;
    char buf[1000]; 
}train_t;
