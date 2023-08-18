#include<c43func.h>
int main(){
    if(fork() == 0){
        printf("I am child pid = %d, ppid = %d", getpid(),getppid());
        while(1){
        printf("I am child pid = %d, ppid = %d", getpid(),getppid());

        };
    }else{

        printf("I am parents pid = %d, ppid =%d\n",getpid(),getppid());
        return 0;
    }
}