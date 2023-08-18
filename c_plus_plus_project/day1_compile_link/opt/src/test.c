#include<stdio.h>
#include"test.h"
int main(){
    #ifdef DEBUG
    int a=12;
    int b=13;
printf("%d",add(a,b));
int c;

#else
printf("there is not DEBUG");
#endif
}
int add(int a,int b){
    return a+b;
}