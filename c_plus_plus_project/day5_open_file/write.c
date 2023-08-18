
#include<c43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int fp = open(argv[1],O_RDWR|O_CREAT,0666); //fp文件描述符 是 内核的描述文件指针数组,指针指向内核的文件对象;  struct_file在这个对象里面  
    ERROR_CHECK(fp,2,"fopen");
    printf("fp=%d\n",fp);
    ftruncate(fp,0);
    char buf[4096]="{0123}dasdaf11asdaf";
    ssize_t ret = write(fp,buf,strlen(buf)); 
  
    printf("%s",buf);
    close(fp);
}