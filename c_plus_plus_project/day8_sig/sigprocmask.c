#include<c43func.h>
void sigfunc(int num){
    printf("%d\n", num);
}
int main(){
    signal(SIGQUIT,sigfunc );  // 注册信号;  pending 集合位图实现; 
    sigset_t set; // 因为mask是一个集合类型
    sigemptyset(&set ); 
    sigaddset(&set,SIGQUIT); // 将
    sigset_t oldset;
    sigprocmask(SIG_SETMASK, &set, &oldset); // 将某个信号整个进程阻塞;
    printf("I am going to sleep!\n");
    sleep(30);
    printf("I wake up\n");
    sigprocmask(SIG_SETMASK, &oldset, NULL); // 

}