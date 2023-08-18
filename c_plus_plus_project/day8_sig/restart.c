#include<c43func.h>
void sigfun(int num){
    printf("before sleep signum = %d\n",num);
    sleep(3);
    printf("after sleep signum = %d\n",num);

}
int main(){

    void (*ret)(int);
    //当信号到来时调用signal函数
    ret = signal(SIGINT,sigfun); // 注册信号; 将信号的功能改成sigfunc 
    ERROR_CHECK(ret, SIG_ERR,"signal");
    ret = signal(SIGQUIT,sigfun);
    ERROR_CHECK(ret, SIG_ERR,"signal");

        char buf[128] = {0};
    read(STDIN_FILENO, buf,sizeof(buf));
    printf("%s\n", buf);

    

}