#include<stdio.h>

int chdig(char*s){
    int i =0;
    int res=0;
    while(s[i]!= '\0'){
        int tmp = s[i]-'0';
        res = res*10 + tmp;
        i++;
    }
    return res;
}
int add(int lhs,int rhs);
int main(int argv,char *argc[]){
    int l,r;
    l = chdig(argc[1]) ;
    r = chdig(argc[1]) ;
	int ret = add(l,r);

    printf("add of two = %d\n",ret);

}
