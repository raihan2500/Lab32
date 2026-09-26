#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd = open("example.txt", O_RDWR);

    char data[] = "Updated";
    lseek(fd, 0, SEEK_END);

    write(fd,"Hello",5);
    close(fd);
}
