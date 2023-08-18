#include<c43func.h>
int main(int argc, char *argv[]){
    printf("\n");
    ARGS_CHECK(argc,2);
    int fp = open(argv[1], O_RDWR);
    int buf = 5;
    printf("you can see me!\n");
    dup2(STDOUT_FILENO,buf);
    close(STDOUT_FILENO); // 这样 STDOUT_FILENO 不会指向任何文件对象
    dup2( fp , STDOUT_FILENO); //  STDOUT_FILENO 是 1
    printf("you can't see me\n");
    dup2(buf , STDOUT_FILENO);
    printf("you can see me!\n");
    
}

