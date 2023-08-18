#include<c43func.h>
int global = 1;
int main(){
    // int stack =2;
    // int *pheap = (int *)malloc(sizeof(int));
    // if(fork() == 0){
    //     printf("I am child process global = %d stack = %d , *pHeap = %d\n",global, stack , *pheap);
    //     ++global ;
    //     ++ stack;
    //  ++ *pheap;
    //  printf("I am child process, global = %d,stack = %d,*pheap = %d\n", global,stack, *pheap);
    // }
    // else{
    //     sleep(10);
    //     printf("I am parent process, global =%d ,stack = %d",global, stack); 
    // }
    printf("hello\n");
    fork();
     printf("world\n");

 }
