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
    int group;
};

int main() {
    int data_cnt = 1024;
    size_t mem_size = sizeof(data_t) * data_cnt;

    data_t *data_private = (data_t *) mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    data_t *data_shared = (data_t *) mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < data_cnt; i++) {
        (data_private + i)->id = i;
        (data_private + i)->group = i % 10;

        (data_shared + i)->id = i;
        (data_shared + i)->group = i % 10;
    }

    int pid = fork();
    if (pid < 0) {
        printf("failed to create child process: %s\n", strerror(errno));
        exit(1);
    } else if (pid == 0) {
        data_private->id = 99;
        data_private->group = 99;
        data_shared->id = 66;
        data_shared->group = 66;
        printf("first of data_private in child become: id=%d, group=%d\n", data_private->id, data_private->group);
        printf("first of data_shared in child become: id=%d, group=%d\n", data_shared->id, data_shared->group);
    } else if (pid > 0) {
        sleep(3);
        printf("first of data_private in parent is: id=%d, group=%d\n", data_private->id, data_private->group);
        printf("first of data_shared in parent is: id=%d, group=%d\n", data_shared->id, data_shared->group);
    }
}
