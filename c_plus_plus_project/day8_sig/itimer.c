#include<c43func.h>
void func(int num){
    time_t now = time(NULL);
    puts(ctime(&now));
    
}
int main(){
    struct itimerval inter;
    inter.it_interval.tv_sec = 5;
    inter.it_interval.tv_usec = 0;
    inter.it_value.tv_sec =1 ;
    inter.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL,&inter, NULL);
    signal(SIGALRM,func);
    while(1){
        
    }
}