#include<c43func.h>
int main(){
    char sentence[] = "./add 3 4";
    char * word;
    word = strtok(sentence, " ");  // 第一个参数只能使用 字符数组; 不能用字面值; 
    printf("word = %s\n", word);

    
    for(int i =0 ; i<4 ; ++i ){
          word = strtok(NULL," ");
    printf("word = %s\n", word);
  
    }

}