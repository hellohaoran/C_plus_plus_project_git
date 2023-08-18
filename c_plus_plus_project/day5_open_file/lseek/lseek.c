#include<c43func.h>
int main(int argc,char * argv[]){
    ARGS_CHECK(argc,2);
    int fp = open(argv[1],O_RDWR|O_CREAT,0666);
    lseek(fp,40960,SEEK_SET);
    char b= 'q';
    write(fp,&b,sizeof(b));
    close(fp);
}