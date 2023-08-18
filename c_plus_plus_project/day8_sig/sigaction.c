



#include<c43func.h>
void sigfun(int num){
    printf("before sleep signum = %d\n",num);
    // signal(SIGINT,SIG_DFL);
}
void sigfun3(int num, siginfo_t * siginfo,void * p){
    printf("num = %d\n", num);
    printf("pid = %d\n", siginfo->si_pid);

}
int main(){

  
    //当信号到来时调用signal函数
    struct sigaction act;
    memset(&act, 0 , sizeof(act)); 
    act.sa_sigaction = sigfun3 ;
    // act.sa_sa_handler = sigfun;
    act.sa_flags =SA_SIGINFO|SA_RESETHAND|SA_NODEFER;  // 属性有SA_SIGINFO则必然将 行为设为sa_sigaction
// SA_RESETHAND 表示只能生效一次
//SA_RESTART 会重启低速的系统调用; 
// SA_SIGINFO 设置了这个属性,只能使用三参数版本的 sa_sigaction  
    int ret = sigaction(SIGINT, &act, NULL); // 信号注册
   
    ERROR_CHECK(ret, SIG_ERR,"signal");
    
    char buf[128] = {0};
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("read = %s", buf);

    while(1){
        
    }
   

    

}