#include<c43func.h>
int main(){
    char * argv[] = {"PATH=/usr/lib",NULL};
    execle("sys_path","./sys_path",NULL,argv);
    
}