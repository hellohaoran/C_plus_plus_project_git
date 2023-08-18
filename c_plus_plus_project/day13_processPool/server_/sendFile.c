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
    // 用4字節表示文件的大小;下面是发送文件的大小信息
    train.len = 4; 
    int filelen = statbuf.st_size;
    memcpy(train.buf, &filelen, sizeof(int));
    send(netFd, &train,sizeof(train.len)+train.len, 0) ;
    // 与mmap文件夹的sendFile相比 这里一次发送了整个文件的内容
    // 从Fd偏移的位置0处开始的filelen长度 ; 
    // mmap将磁盘的文件通过内核的文件描述符映射到内存地址空间;

    /*
    printf("filelen = %d\n", filelen ); 
    char *p = (char *)mmap(NULL, filelen , PROT_READ|PROT_WRITE, MAP_SHARED,Fd, 0) ; 
    ERROR_CHECK(p , MAP_FAILED, "mmap"); 
    send(netFd, p ,filelen ,MSG_NOSIGNAL ) ;
  */
    sendfile(netFd,Fd, NULL, filelen); 

    train.len = 0 ;
    ret = send(netFd, &train, sizeof(train.len)+train.len,MSG_NOSIGNAL);
   
    close(Fd);
    // munmap(p , filelen); 

}