#include<c43func.h>
int main(){
    pid_t pid = fork();
    if(pid == 0){
        printf("I am child pid = %d ppid = %d sid = %d\n", getpid(), getppid() , getsid(0));
        setsid();
        printf("I am child pid = %d ppid = %d sid = %d\n", getpid(), getppid() , getsid(0));

    }else{
        printf("I am father pid = %d ppid = %d sid = %d\n",getpid(), getppid(), getsid(0));
        while(1);
        wait(NULL);
        exit(0);

    }
}