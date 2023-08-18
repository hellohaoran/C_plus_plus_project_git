#include<c43func.h>
int main(int argc, char*argv[]){
    ARGS_CHECK(argc, 3);
    int sig = atoi(argv[1]+1);
    int pid = atoi(argv[2]);
    kill(pid ,sig);
}