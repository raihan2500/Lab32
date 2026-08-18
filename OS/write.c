#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd;
    int data = 100;
    fd = open("data.bin", O_RDWR);

    if(fd < 0){
        write(1, "failed\n",7);
        return 1;
    }

    write(fd, &data, sizeof(data));
    close(fd);
    
    write(2, "successfull\n",12);

}