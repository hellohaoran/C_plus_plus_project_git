#include<c43func.h>
int main(){
    // 大端和小端的转换; 
    unsigned short s  = 0x1234;
    printf("s = %x\n",s);
    printf("htons(s) = %x\n", htons(s)); 
    unsigned int i = 0x15456;
    printf("htonl(i) = %x\n", htonl(i));     
}