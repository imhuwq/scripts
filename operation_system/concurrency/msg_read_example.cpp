#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <cerrno>
#include <cstring>

struct msg {
    long mtype;
    char mdata[6];
};

int main() {
    key_t key;
    if ((key = ftok("/", 'A')) <= 0) {
        printf("failed to get key: %s\n", strerror(errno));
        exit(1);
    } else {
        printf("ftkey: %d\n", key);
    }

    int msg_id = msgget(key, IPC_CREAT | 0666);
    if (msg_id < 0) {
        printf("failed to get message queue: %s\n", strerror(errno));
        exit(1);
    } else {
        printf("msg_id: %d\n", msg_id);
    }

    msg m;
    while (true) {
        if (msgrcv(msg_id, &m, sizeof(msg), 3, 0) < 0) {
            printf("failed to receive msg: %s\n", strerror(errno));
            exit(1);
        }
        printf("%s\n", m.mdata);
    }
}