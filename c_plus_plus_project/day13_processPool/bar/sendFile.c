#include <c43func.h>
#include "head.h"
int sendFile(int netFd)
{
    int Fd = open("file1", O_RDWR);
    
    // 发给对方文件名
    train_t train;
    train.len = 5;
    strcpy(train.buf, "file1");
    int ret = send(netFd, &train, sizeof(train.len) + train.len, 0);
    struct stat statbuf;
    ret = fstat(Fd , &statbuf);
    ERROR_CHECK(ret , -1, "fstat");
    // 用4字節表示文件的大小
    train.len = 4; 
    int filelen = statbuf.st_size;
    memcpy(train.buf, &filelen, sizeof(int));
    send(netFd, &train,sizeof(train.len)+train.len, 0) ;
   while(1){
        bzero(&train, sizeof(train));
        ret = read(Fd, train.buf, sizeof(train.buf));
       
   
        if(ret == 0){
            break; 
        }
        train.len = ret;
        // 发给对方文件的信息
        ret = send(netFd, &train, sizeof(train.len) + train.len, MSG_NOSIGNAL);
        

   }
    train.len = 0 ;
    ret = send(netFd, &train, sizeof(train.len)+train.len,MSG_NOSIGNAL);
   
    close(Fd);


}