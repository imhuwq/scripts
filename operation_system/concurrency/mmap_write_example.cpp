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

    int fd = open(file, O_RDWR, 0666);
    if (fd < 0) {
        printf("failed to open file: %s\n", strerror(errno));
        exit(1);
    }

    size_t file_size = sizeof(char) * 4096;
    data_t *ptr = (data_t *) mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == NULL) {
        printf("failed to map file: %s\n", strerror(errno));
        exit(1);
    }
    close(fd);

    ptr->id += 1;
    char label[4] = "WRT";
    memcpy(ptr->label, label, 4);

    while (true) {
        sleep(1);
    }
    munmap(ptr, file_size);
}
