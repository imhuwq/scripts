#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

struct data_t {
    int id;
    char label[4];
};

int main() {
    char *file = "/tmp/testmmap";

    int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        printf("failed to open file: %s\n", strerror(errno));
        exit(1);
    }
    size_t file_size = sizeof(char) * 4096;

    char *buf = (char *) malloc(file_size);
    char label[4] = "CRT";
    size_t data_cnt = file_size / sizeof(data_t);
    data_t *data_buf = (data_t *) buf;
    for (int i = 0; i < data_cnt; i++) {
        (data_buf + i)->id = i;
        memcpy((data_buf + i)->label, label, 4);
    }
    lseek(fd, 0, SEEK_SET);
    write(fd, buf, file_size);
    
    sleep(10);
    close(fd);
}
