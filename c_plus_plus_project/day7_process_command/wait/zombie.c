#include<c43func.h>
int main(){
    pid_t pid;
    pid = fork();
    if(pid == 0){ // 子进程
       
        printf("I am child pid=%d ppid=%d",getpid(),getppid());
      abort();
    //    sleep(10); 

    } else if (pid == -1){
       ERROR_CHECK(pid, -1 ,"fork");
    }else{ //   
    //    sleep(1);
        printf("I am father pid=%d ppid=%d",getpid(),getppid());

    int wstatus; // 存储子进程终止情况
    while (1)
    {
      int _pid = waitpid(-1,&wstatus,WNOHANG ); // 
    if(0 == _pid){
        printf("no child exit!\n");
    }else if(_pid > 0){
        if(WIFEXITED(wstatus)){
            printf("Normal exit! Return value = %d\n", WEXITSTATUS(wstatus));
        }else if(WIFSIGNALED(wstatus)){ // 返回true 如果 子进程 被一个信号终结; 
            printf("abnormal exit!Terminal signal = %d\n", WTERMSIG(wstatus));
        }
        break; // 
    }
    }  
    }
    
  

}