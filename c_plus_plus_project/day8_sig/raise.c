#include<c43func.h>
void sigfunc(int num){
    printf("num = %d\n",num);
}
int main(){
    // raise 适用于有序终止
    signal(SIGINT, sigfunc);
    while(1){
        getchar();
        raise(2);
    }

}