#include<c43func.h>
int main(){
    if(fork() == 0) {
        printf("I am child process, pid =%d ; pgid  = %d\n" , getpid(), getpgid(0) );
        
        setpgid(0,0); // 将 pid设置成新的组id; 
        printf("I am child process, pid = %d pgid = %d\n",getpid(),getpgid(0));
        while(1);
    }else{
        printf("I am parent process, pid = %d, pgid = %d\n", getpid(),getpgid(0));
        wait(NULL);
    }
}