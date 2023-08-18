#include<c43func.h>

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
typedef struct train_s{
    int len;
    char buf[1000]; 
}train_t;
int recvFile(int sockFd){
  // 先获取文件名
  char name[1024] = {0};
  // 自定义私有协议先接收数据长度; 
  int datalen ;  
  int ret = recv(sockFd,&datalen, sizeof(int), 0 );
  ERROR_CHECK(ret , -1 , "recv"); 
  ret = recv(sockFd , name , datalen , 0);
  ERROR_CHECK(ret, -1 , "recv"); 
  int fd  = open(name ,O_CREAT |O_RDWR|O_TRUNC,0666);
  ERROR_CHECK(fd , -1 , "open") ; 
  char buf[1024] = {0};
  ret = recv(sockFd, &datalen ,sizeof(int) , 0);
  ERROR_CHECK(ret , -1 , "recv"); 
  ret = recv(sockFd , buf ,datalen, 0);
  ERROR_CHECK(ret , -1 , "recv"); 
  write(fd, buf , ret ) ;
  close(fd) ; 

}

int main(int argc, char* argv[]){
   
  
    int sockFd = socket(AF_INET ,SOCK_STREAM,0 );
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    int ret = connect(sockFd, (struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret , -1 , "connect");
    recvFile(sockFd); 
    close(sockFd);

    // connect()
    
    }