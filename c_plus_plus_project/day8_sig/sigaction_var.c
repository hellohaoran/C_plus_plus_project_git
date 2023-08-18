#include<c43func.h>
void sigfunc(int num){
    printf("num = %d\n",num);
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    
    if(sigismember(&pending, SIGQUIT)){
        printf("SIGQUIT is pending!\n");
    }else{
        printf("SIGQUIT is pending!\n");
    }
    sleep(5);
}
int main(){
    signal(SIGINT, sigfunc);
sigset_t     set , oldset;
    sigemptyset(&set);
    // 将SIGQUIT加入阻塞
    sigaddset(&set, SIGQUIT); 

    sigprocmask(SIG_SETMASK ,&set,&oldset );
while(1);
}