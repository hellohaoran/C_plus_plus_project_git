#include <c43func.h>

// int main(int argc,char *argv[]){
//       // ./client 192.168.77.129 1234
//     // ./server_v3  192.168.77.129 1234
//     // socket connect select send recv
//     ARGS_CHECK(argc,3);
//     //读网络->recv会阻塞; 读标准输入会阻塞
//     int sockFd = socket(AF_INET, SOCK_STREAM, 0);
//     // struct sockaddr_in 在man 7 ip
//     struct sockaddr_in addr ;
//     addr.sin_addr.s_addr = inet_addr(argv[1]);
//     addr.sin_port = htons(atoi(argv[2]));
//     addr.sin_family = AF_INET;
//     int ret = connect(sockFd, (struct sockaddr*)&addr, sizeof(addr));
//     ERROR_CHECK(ret , -1 , "connect");
//     sleep(5);
//     close(sockFd);

// }

// 由于有粘包:TCP字节流; 不区分文件名和文件内容; 所以创建自定义的私有协议:
typedef struct train_s
{
  int len;
  char buf[1000];
} train_t;
// 由于recv的MSG_WAITALL 参数有一定的bug;
//所以自己实现一个按照指定的数量收数据的函数
int recvn(int sockFd, void *pstart,int len){
  // pstart是起始地址;len要收到字节数;

  int total = 0;  //统计当前已收到的字节;
  int ret ;
  char* p = (char*)pstart ;
  while(total<len){
    // 一直向sockFd收數據
    ret = recv(sockFd, p+total , len - total,0);
    total += ret; 
  }
  return 0;
}
int recvFile(int sockFd)
{
  // 先获取文件名
  char name[1024] = {0};
  // 自定义私有协议先接收数据长度;
  int datalen;
  // int ret = recv(sockFd, &datalen, sizeof(int), MSG_WAITALL);
  int ret = recvn(sockFd, &datalen, sizeof(int));
  ERROR_CHECK(ret, -1, "recv");
  // ret = recv(sockFd, name, datalen, MSG_WAITALL);
   ret = recvn(sockFd, name, datalen);
  ERROR_CHECK(ret, -1, "recv");
  int fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
  ERROR_CHECK(fd, -1, "open");
  char buf[1000] = {0};
  // 一直
  while (1)
  {
    // ret = recv(sockFd, &datalen, sizeof(int), MSG_WAITALL);
    ret = recvn(sockFd, &datalen, sizeof(int));
    // if(ret == 0){// 断开连接ret 才为0;
    //   break;
    // }
    if (datalen != 1000)
    {
      printf("datalen = %d\n", datalen);
    }
    if (datalen == 0)
    {
      break;
    }
    ERROR_CHECK(ret, -1, "recv");
    // ret = recv(sockFd, buf, datalen, MSG_WAITALL);
    ret = recvn(sockFd, buf, datalen) ; 
    ERROR_CHECK(ret, -1, "recv");
    write(fd, buf, datalen);
  }
  close(fd);
}

int main(int argc, char *argv[])
{

  int sockFd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  int ret = connect(sockFd, (struct sockaddr *)&addr, sizeof(addr));
  ERROR_CHECK(ret, -1, "connect");
  recvFile(sockFd);
  close(sockFd);

  // connect()
}