#include <stdio.h>
#include <string.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/stat.h>
// #include <sys/types.h>
#include "file.h"

int main(){
    // int fd = open("test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    // if (-1 == fd) {
    //     write(2, "open file wrong!\n", strlen("open file wrong!\n"));
    //     close(fd);
    // }
    // if (strlen("test info!") != write(fd, "test info!", strlen("test info!"))) {
    //     write(2, "write file wrong!\n", strlen("write file wrong!\n"));
    // }
    // close(fd);
    
    file f("test.txt");
    char bytes[] = {0x01,0x02,0x03,0x04,0x12,0x21};
    f.write_binary(bytes, 6);

    return 0;
}