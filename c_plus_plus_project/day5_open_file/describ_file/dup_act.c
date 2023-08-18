#include<c43func.h>
int main(int argc, char *argv[]){
    printf("\n");
    ARGS_CHECK(argc,2);
    int olddp = open(argv[1],O_RDWR|O_TRUNC);
    ERROR_CHECK(olddp ,-1 , "open");
    close(STDOUT_FILENO);
    int newdp = dup(olddp); // dup 会将最小可用的文件描述符作为克隆出来的文件描述符
    ERROR_CHECK(olddp ,-1 , "open");

    printf("olddp = %d",olddp);
    printf("newdp = %d",newdp);
close(olddp); // 猜测 有了close 就 会在printf结束之前 清空 olddp
close(newdp);
printf("%d",olddp);


    
    }