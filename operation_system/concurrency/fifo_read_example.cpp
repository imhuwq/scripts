#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include<fcntl.h>

int main() {
    int fd = open("/tmp/testfifo", O_RDONLY);
    if (fd < 0) {
        printf("failed to create fifo: %s\n", strerror(errno));
        exit(1);
    }

    char msg[6];

    while (true) {
        read(fd, msg, 6);
        printf("%s\n", msg);
    }
}