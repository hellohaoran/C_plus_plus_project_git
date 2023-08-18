#include<c43func.h>
int main(int argv,char *argc[]){
    ARGS_CHECK(argv,2);
    int ret = rmdir(argc[1]);
    ERROR_CHECK(ret,NULL,"redir");
}