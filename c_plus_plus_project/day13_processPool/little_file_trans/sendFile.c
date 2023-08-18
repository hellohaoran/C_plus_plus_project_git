#include <c43func.h>
#include "head.h"
int sendFile(int netFd)
{
    int Fd = open("file1", O_RDWR);
    ERROR_CHECK(Fd, -1, "open");
    // 发给对方文件名
    train_t train;
    train.len = 5;
    strcpy(train.buf, "file1");
    int ret = send(netFd, train.buf, sizeof(train.len) + train.len, 0);
    bzero(&train, sizeof(train));
    ret = read(Fd, train.buf, sizeof(train.buf));
    ERROR_CHECK(ret, -1, "read");
    train.len = ret;
    // 发给对方文件的信息
    ret = send(netFd, &train, sizeof(train.len) + train.len, 0);
    ERROR_CHECK(ret, -1, "send");
    close(Fd);
}