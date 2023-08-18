#include<c43func.h>
#define N 1000000
int main(){
    int t[1] = {0};
    struct timeval beg,end;
    gettimeofday(&beg,NULL);
    if(fork() == 0){
        for(int i =0;i<N;++i){
                t[0]++;
        }

    }else{
        wait(NULL);
         for(int i =0;i<N;++i){
                t[0]++;
        }
       

    }
     gettimeofday(&end,NULL);
        time_t s = end.tv_sec - beg.tv_sec;
        time_t us = end.tv_usec - beg.tv_usec;
        if(us < 0){
            us = us + 1000000;
            --s; 
        }
        printf("%d",t[0]);
        printf("time consum = %ld s %ld us\n", s,us);
}