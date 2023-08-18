#include<c43func.h>
int main(int argc , char*argv[]){
    ARGS_CHECK(argc ,2 );
    int fd = open(argv[1], O_RDWR|O_CREAT, 0776);
    int ret = write(fd , "hell0",6);
    ERROR_CHECK(ret ,-1 ,"write");
    
    printf("uid = %d, euid = %d", getuid(),geteuid());
    printf("gid = %d,egid = %d ",getgid(),getegid());

    while(1);


}