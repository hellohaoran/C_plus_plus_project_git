#include<c43func.h>
void sigfunc(int num){
    printf("num = %d\n",num);
}
int main(){
    signal(SIGINT, sigfunc);
    pause();
}