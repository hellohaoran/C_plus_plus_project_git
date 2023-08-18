#include<c43func.h>
int main(int argc,char * argv[]){
    ARGS_CHECK(argc,2);
    int fp = open(argv[1],O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fp,-1,"open");
    int ret = ftruncate(fp,5);
     char *mp= mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fp,0); 
     ERROR_CHECK(mp,NULL,"mmap");

     for(int i =0;i<5;++i){
        printf("%c",mp[i]);
     }
     mp[2]= '5';
      munmap(mp,5); // 在调用munmap时进程对文件的操作会写入磁盘中

}