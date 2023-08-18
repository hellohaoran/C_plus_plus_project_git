#include<c43func.h>
int main(){
    int pipFd[2];
    pipe(pipFd);
    if(fork()){
        // 子进程读;
        close(pipFd[1]);
        struct iovec iov[1];
        char buf[10]= {0};
        iov[0].iov_base =buf;
        iov[0].iov_len = sizeof(buf);
        readv(pipFd[0], iov,1);
        
        puts(buf);


    }else{
        //父进程写
        close(pipFd[0]);
        struct iovec iov[1];
        char buf[10] = "hello";
        iov[0].iov_base = buf;
        iov[0].iov_len = sizeof(buf);
        writev(pipFd[1], iov,1);

    }
}