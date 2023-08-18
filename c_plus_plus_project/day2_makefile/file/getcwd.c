#include<c43func.h>
int main(){
    // char ch[1024];
    // char *ret = getcwd(ch,sizeof(ch));  // ret是指向ch的内容;
    // ERROR_CHECK(ret,NULL,"getcwd");
    // printf("%p   %s\n",ret, ret);
    // printf("%p   %s\n",ch, ch);
    char * ret = getcwd(NULL,0); // 为NULL时malloc自动分配空间 
    printf("%p   %s",ret,ret);
    free(ret);
}