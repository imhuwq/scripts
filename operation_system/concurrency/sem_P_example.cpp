#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static sembuf opP;
static sembuf opV;

void P(int sem_id) {
    while (semop((sem_id), &opP, 1) < 0) {
        if (errno == EINTR) continue;
        printf("P error: %s\n", strerror(errno));
    }
}

void V(int sem_id) {
    while (semop((sem_id), &opV, 1) < 0) {
        if (errno == EINTR) continue;
        printf("V error: %s\n", strerror(errno));
    }
}

key_t get_key(char *file, char id) {
    key_t key = ftok(file, id);
    if (key <= 0) {
        printf("failed to get key: %s\n", strerror(errno));
        exit(1);
    }
    return key;
}

void init_PV() {
    opP.sem_num = 0;
    opP.sem_flg = 0;
    opP.sem_op = -1;

    opV.sem_num = 0;
    opV.sem_flg = 0;
    opV.sem_op = 1;
}

int create_sim(key_t key) {
    int sem_id = semget(key, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        printf("failed to create sem: %s\n", strerror(errno));
        exit(1);
    }

    if (semctl(sem_id, 0, SETVAL, 0) < 0) {
        printf("failed to init sem: %s\n", strerror(errno));
        exit(1);
    }

    init_PV();

    return sem_id;
}

int main() {
    char *file = "/tmp/testsem";
    char project_id = 'Z';
    key_t key = get_key(file, project_id);
    int sem_id = create_sim(key);

    while (true) {
        printf("acquiring sem...\n");
        P(sem_id);
        printf("acquiring sem success...\n");
    }
}