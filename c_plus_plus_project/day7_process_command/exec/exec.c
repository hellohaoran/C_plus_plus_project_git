#include<c43func.h>
int main(){
    printf("before exec ! pid = %d, ppid = %d\n",getpid(), getppid());
    execl("add","./add","15","75",NULL);
    printf("after execl !"); // 不会执行,因为代码段, 堆 , 栈 数据段 会被清空;

}