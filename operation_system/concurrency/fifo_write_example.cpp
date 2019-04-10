#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include<fcntl.h>

int main() {
    int fd = mkfifo("/tmp/testfifo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0 && errno == EEXIST) {
        fd = open("/tmp/testfifo", O_RDWR);
    }
    if (fd < 0) {
        printf("failed to create fifo: %s\n", strerror(errno));
        exit(1);
    }

    char msg[6];
    sprintf(msg, "%s", "hello");
    while (true) {
        write(fd, msg, 6);
        sleep(1);
    }
}