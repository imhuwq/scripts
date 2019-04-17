#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    int r_w[2];
    int ok = pipe(r_w);
    if (ok == -1) {
        printf("failed to open pipe: %s\n", strerror(errno));
        exit(1);
    }

    int read_fd = r_w[0];
    int write_fd = r_w[1];
    pid_t pid = fork();

    if (pid == 0) {
        char buf[10];
        if (read(read_fd, buf, 10) == -1) {
            printf("failed to read pipe: %s\n", strerror(errno));
            exit(1);
        }
        printf("%s\n", buf);
    } else {
        char buf[10] = "12345abcd";
        if (write(write_fd, buf, 10) == -1) {
            printf("failed to write pipe: %s\n", strerror(errno));
            exit(1);
        }
        sleep(1);
    }
}