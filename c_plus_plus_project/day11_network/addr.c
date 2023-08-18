#include<c43func.h>
int main(int argc , char* argv[]){
     ARGS_CHECK(argc , 3);
     struct sockaddr_in addr; //  从 小端转换成 网络层 的大端 地址
     addr.sin_family = AF_INET; // 表示使用IPV4 
     addr.sin_port = htons(atoi(argv[2])) ; // 设计所用的端口号用16位表示;将端口号转换成网络的大端
     addr.sin_addr.s_addr =  inet_addr(argv[1]) ;  
    printf("port = %x\n",addr.sin_port );
    printf("ip = %x\n", addr.sin_addr.s_addr); 


}