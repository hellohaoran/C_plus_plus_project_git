#include<c43func.h>
int main(int argc,char*argv[]){
    ARGS_CHECK(argc,3);
    int sfp = open(argv[1],O_RDONLY); 
    int dfp = open(argv[2],O_RDWR|O_CREAT,0666);
    char buf[4096];
    while(1){
        memset(buf,0,sizeof(buf));
        int ret = read(sfp,buf,sizeof(buf));
        if(ret == 0){
            break;
        }
        ERROR_CHECK(ret , -1,"read");
        write(dfp,buf,ret); // 写到要拷贝的文件
    }
    close(sfp);
    close(dfp);
    
}