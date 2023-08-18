#include<c43func.h>
int main( int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1], O_RDONLY); // 管道是在open的时候阻塞的
    puts("pip open");
    char buf[4096]={0};
    int ret = read(fd , buf, sizeof(buf));
    ERROR_CHECK(ret ,-1, "read");
    puts(buf);
    close(fd );
}