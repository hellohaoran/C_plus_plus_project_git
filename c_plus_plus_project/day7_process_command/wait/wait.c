#include<c43func.h>
int main(){
    pid_t pid;
    pid = fork();
    if(pid == 0){ // 子进程
        printf("I am child pid=%d ppid=%d",getpid(),getppid());

    } else if (pid == -1){
       ERROR_CHECK(pid, -1 ,"fork");
    }else{ //   
       
        printf("I am father pid=%d ppid=%d",getpid(),getppid());
        wait(NULL); // 在子进程终止时就绪 ; 将子进程资源回收掉; 
    }
}