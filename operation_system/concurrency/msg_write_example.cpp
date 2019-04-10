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

#define count 6
    msg msg_array[count];
    char * word[count] = {"hello", "world", "happy", "codes", "great", "minds"};
    for (int i = 0; i < count; i++) {
        msg_array[i].mtype = (i >> 1) + 1;
        memcpy(&(msg_array[i].mdata), word[i], 6 * sizeof(char));

        if (msgsnd(msg_id, &msg_array[i], sizeof(msg), 0) < 0) {
            printf("failed to write msg: %s\n", strerror(errno));
            exit(1);
        }
    }
}