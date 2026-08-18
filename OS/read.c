#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main(){
    int data;
    int fd = open("data.bin", O_RDONLY);
    int dest = open("copy.jpg", O_CREAT | O_WRONLY | O_TRUNC, 0777);

    char buffer[4096];
    int bytes;
    while((bytes = read(fd, buffer, sizeof(buffer))) > 0){
        write(dest, buffer, bytes);
    }
    close(dest);
}