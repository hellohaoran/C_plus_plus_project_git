#include<c43func.h>
void sigFunc(int signum){
    // 输入打断符后, 换行后,另外打印
    printf("\n%s$",getcwd(NULL,0));
    fflush(stdout);
}
int main(){
    signal(SIGINT, sigFunc);
    while(1){
        //bash进程输出$, 之后创建子进程去执行输入的命令; 
        printf("%s$",getcwd(NULL,0)); // 输入命令
        fflush(stdout);
         //用来接住输入的命令
        char cmd[4096] = {0};
        //
        read(STDIN_FILENO, cmd, sizeof(cmd)) ;
        //将换行符替换掉
        cmd[strlen(cmd)-1] = 0;
        if(fork() == 0){
            signal(SIGINT,SIG_DFL);
            char * argvector[100] = {0};
            // 将输入的命令进行切割
            argvector[0] = strtok(cmd, " ");
            int i =1; 
            while(argvector[i] != NULL){
                argvector[i] = strtok(NULL," ");
                i++;
            }
            //此时命令各参数准备好,进行执行命令;
            execv(argvector[0],argvector);
            

        } else{
            wait(NULL);
        }

    }
}