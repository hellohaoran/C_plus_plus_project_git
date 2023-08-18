#include<c43func.h>
int main(int argc,char * argv[]){
    // 证明了内存的fopen文件缓冲区的底层实现是用了 内核的文件结构体   
    // 代码要清晰易懂 , 代码即注释   
    ARGS_CHECK(argc,2);
    FILE*fp = fopen(argv[1], "r+");
    ERROR_CHECK(fp,NULL,"fopen");
    // printf("fileno = %d\n",fp->_fileno); // 参数名前有"_" 表示不建议访问
    printf("fileno = %d\n",fileno(fp)); // 用函数去访问 ---> 面向接口编程 
    
    int ret = write(fp->_fileno,"hello", 5);
    ERROR_CHECK(ret,-1,"write");
    fclose(fp);

    
    }