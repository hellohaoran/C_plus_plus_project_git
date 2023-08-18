#include<c43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int fp = open(argv[1],O_WRONLY|O_CREAT,0666);
    ERROR_CHECK(fp,2,"fopen");
    printf("fp=%d\n",fp);

    close(fp);
}