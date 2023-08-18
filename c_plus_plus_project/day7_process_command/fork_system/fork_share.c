#include<c43func.h> 
int main(){
    int fd = open("file1",O_RDWR);
    ERROR_CHECK(fd , -1,"open");
    if(fork() == 0){
        write(fd,"hello",5);

    }
    else{
        sleep(5);
        write(fd, "hey open", 8);
    }
}