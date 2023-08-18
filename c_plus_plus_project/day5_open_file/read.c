
#include<c43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int fp = open(argv[1],O_RDONLY|O_TRUNC,0666);
    ERROR_CHECK(fp,2,"fopen");
    printf("fp=%d\n",fp);
    char buf[4096]={0};
    int ret = read(fp,buf,sizeof(buf));

    printf("%s",buf);
    close(fp);
}