#include<stdio.h>
int chdig(char * s){
int i =0;
int ret =0 ;          
while(s[i]!= '\0'){
int tep = s[i]-'0';
ret = tep  + ret*10;
++i;
int a = 15;
printf("")
}
return ret;
}

int add(int lhs,int rhs);
int main(int argc,char *argv[]){
int i = 10,j =20;
//scanf("%d,%d",&i,&j);
 i = chdig(argv[1]);
 j = chdig(argv[2]);
int ret = j+i;
printf("add of two = %d",ret);

}
