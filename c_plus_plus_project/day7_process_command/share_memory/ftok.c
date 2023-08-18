#include<c43func.h>
int main(){
    key_t k =ftok("./file1",1);
    ERROR_CHECK(k,-1,"ftok");
    printf("ipc key = %d",k);
}