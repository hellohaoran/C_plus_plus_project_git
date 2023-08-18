#include<c43func.h>
int main( int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1], O_WRONLY);
    puts("pip open"); 
    char buf[4096]="hello";
    int ret = write(fd , buf, sizeof(buf));
    ERROR_CHECK(ret ,-1, "write");
close(fd);
}