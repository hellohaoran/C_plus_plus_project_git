#include<c43func.h>
int main(int argc,char * argv[]){
    // popen w模式 向子进程输入; 
    FILE * fp = popen(argv[1], "w");
    ERROR_CHECK(fp,NULL, "popen");
    fwrite("100 50",7,1,fp);
    
}