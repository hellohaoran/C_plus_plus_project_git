#include<c43func.h>
int main(){
    if(fork() == 0){
        printf("I am child , pid = %d, ppid = %d, pgid = %d\n", getpid(), getppid(),getpgrp());
        setpgid(0,0);
        printf("I am child , pid = %d, ppid = %d, pgid = %d\n", getpid(), getppid(),getpgrp());
        while(1);

    }else{
        int wstatus;
        waitpid(0,&wstatus,WNOHANG);
        printf("I am father , pid = %d, ppid =%d , pgid = %d\n ", getpid(),getppid(), getpgrp());
        while(1); // 父进程

    }
}