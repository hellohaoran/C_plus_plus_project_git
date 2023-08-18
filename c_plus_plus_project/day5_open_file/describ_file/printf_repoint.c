#include<c43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    printf("you can see me!\n");
    close(STDOUT_FILENO);
    int fp = open(argv[1],O_RDWR,0666);
    printf("this is you");
    

}