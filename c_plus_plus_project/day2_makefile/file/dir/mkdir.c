#include<c43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2); // 检查参数
    int ret = mkdir(argv[1],0777);  // 0777 代表三个八进制数
    // 受到umask的影响 ; 会变成775(与umask的反码与)
    ERROR_CHECK(ret,-1,"mkdir");

}
