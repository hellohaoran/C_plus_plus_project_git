#include<c43func.h>

int main(int argv,char * argc[]){
// 格式:./chmod 777 file

ARGS_CHECK(argv,3);
mode_t mode;
printf("%d",atoi(argc[1]));
sscanf(argc[1],"%o",&mode);
int ret = chmod(argc[2],mode);
ERROR_CHECK(ret,-1,"chmod");




}