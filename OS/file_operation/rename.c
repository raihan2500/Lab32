#include<unistd.h>
#include<fcntl.h>
#include <sys/syscall.h>
#include<stdio.h>


int main(){
    int res;
    res = syscall(SYS_rename, "data.bin", "temp.bin");

    if(res == 0){
        printf("successful\n");
    }else{
        printf("Failed\n");
    }
}