#include<stdio.h>
void func(int i){
printf("I am func , i = %d\n",i);
}
int main(int argc,char *argv[]){
	int i =10;
	int a[3]= {1,2,3};
	int *p;
	a[2] = 4 ;
	func(i);
	
	p = a;
	for(int j =0;j<i;++j ){
	printf("%d\n",p[i]);
	}

	return 0;}
