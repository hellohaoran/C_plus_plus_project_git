#include<c43func.h>
void func(int num){
    printf("num = %d",num);
}
int main(){
    struct sigaction act;
    act.sa_handler = func;
    act.sa_flags = SA_RESTART;
    sigaction(SIGALRM,&act,NULL);
    printf("before alarm!\n");

sigset_t set;
sigset_t oldset;
sigaddset(&set, SIGALRM);
sigprocmask(SIG_SETMASK, &set, &oldset); // 将原先的集合保存到oldset; 
    alarm(1);
 
    sigprocmask(SIG_SETMASK, &oldset,NULL); // 解除阻塞
   pause(); 

    // pause();


    }