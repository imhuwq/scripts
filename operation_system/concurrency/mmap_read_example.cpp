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

    int fd = open(file, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        printf("failed to open file: %s\n", strerror(errno));
        exit(1);
    }

    data_t *data_array = (data_t *) mmap(NULL, sizeof(data_t) * 3, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data_array == NULL) {
        printf("failed to map file: %s\n", strerror(errno));
        exit(1);
    } else {
        close(fd);
    }

    printf("first three data:\n");
    for (int i = 0; i < 3; i++) {
        printf("\tdata_t %d: id=%d, label=%s\n", i, (data_array + i)->id, (data_array + i)->label);
    }
    printf("=========\n");

    printf("first data: \n");
    while (true) {
        printf("\tdata_t 0: id=%d, label=%s\n", data_array->id, data_array->label);
        sleep(1);
    }
}
