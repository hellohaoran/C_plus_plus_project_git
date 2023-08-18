#include<c43func.h>
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int oldfp = open(argv[1], O_RDWR);
    ERROR_CHECK(oldfp,-1,"open"); //
    int fp = dup(oldfp);
    printf("oldfp = %d",oldfp);
    printf("newfp = %d",fp);
    write(fp,"Hello",5);
    close(fp);
    write(oldfp,"world",5); // dup 函数可以像使用 oldfp一样使用fp 

}