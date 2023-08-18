#include<c43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc , 2);
    int fdr = open(argv[1],O_RDWR);
    int fdw = open(argv[1],O_RDWR); 
    fd_set fdrset;
    fd_set fdwset;
    char buf[4096]={0};
    while(1){
        memset(buf,0,sizeof(buf));
        FD_ZERO(&fdrset);
        FD_SET(fdr,&fdrset) ;
      FD_ZERO(&fdwset);
        FD_SET(fdw,&fdwset) ;
        select(fdw+1,&fdrset,&fdwset,NULL,NULL); 
if(FD_ISSET(fdr, &fdrset)){
    printf("读端就绪");
    read(fdr, buf, 2048);
    puts(buf);
}
if(FD_ISSET(fdw,&fdwset)){
    printf("写端就绪");

    write(fdw,buf,sizeof(buf));
    
}
sleep(1);


    
    }

}