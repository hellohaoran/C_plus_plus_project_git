#include<c43func.h>
// #include<>
int main(int argc,char * argv[]){
    ARGS_CHECK(argc,2);
     // ./chdir dir1
    printf("beforea chdir, cwd = %s\n",getcwd(NULL,0));
    int num = chdir(argv[1]);
    if(num == -1){
        
        return -1;
    } 
    printf("after chdir , cwd = %s\n",getcwd(NULL,0));
    
}