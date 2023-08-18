#include<c43func.h>
void sigfunc(int num){
   
    time_t  now = time(NULL);
    printf("%s\n",ctime(&now));
   


}
int main(){
    time_t now = time(NULL);
    printf("%s\n",ctime(&now));
    alarm(3);
    signal(SIGALRM, sigfunc);
      pause();
    
    
}