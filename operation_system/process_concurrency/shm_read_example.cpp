#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct data_t {
    int id;
    int group;
};


int main() {
    char *shm_file = "/dev/shm/A";
    char project_id = 'A';
    key_t key = ftok(shm_file, project_id);
    if (key < 0) {
        printf("failed to get key: %s\n", strerror(errno));
        exit(1);
    }

    int data_cnt = 1024;
    size_t mem_size = sizeof(data_t) * data_cnt;
    int shm_id = shmget(key, mem_size, IPC_CREAT | 0666);
    if (shm_id <= 0) {
        printf("failed to get shm id: %s\n", strerror(errno));
        exit(1);
    }

    data_t *data_ptr;
    data_ptr = (data_t *) shmat(shm_id, NULL, 0);
    if (data_ptr == NULL) {
        printf("failed to create shared memory: %s\n", strerror(errno));
        exit(1);
    }

    for (int i = 0; i < data_cnt; i++) {
        printf("data_t %d: id=%d, group=%d\n", i, (data_ptr + i)->id, (data_ptr + i)->group);
    }

}