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
    addr.sin_family = AF_INET; 
    int ret = connect(sockFd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(ret , -1 , "connect");
    char buf[1024] = {0};
    // 原则是哪个文件描述符需要异步访问,哪个就加入集合
    
    read(STDIN_FILENO ,buf,sizeof(buf) );
    sleep(5);
    send(sockFd , buf, strlen(buf) , 0);
   
    close(sockFd);


    

}