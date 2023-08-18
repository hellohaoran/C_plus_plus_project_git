#include<c43func.h>
int main(){
    // popen 是 匿名管道; 创建子进程; 子进程的stdout 重定向到 管道
    // popen  r 模式读取子进程的输出
    FILE * fp = popen("./print","r"); 
    ERROR_CHECK(fp,NULL,"popen");
    char buf[1024] = {0};
    fread(buf, sizeof(buf), 1, fp);
    printf("msg from print : %s\n",buf);
}