#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>

int g = 5;

int main() {
    int l = 3;

    pid_t pid = fork();
    if (pid == 0) {
        l += 1;
        printf("child process: pid=%d, g=%d, l=%d\n", pid, g, l);

        char * argv_list[] = {"/bin/ls","/",NULL};
        int ok = execv("/bin/ls", argv_list);

        if (ok == -1) {
            printf("failed to replace process: %s\n", strerror(errno));
        }
        printf("child process: pid=%d, g=%d, l=%d\n", pid, g, l);
    } else {
        printf("parent process: pid=%d, g=%d, l=%d\n", pid, g, l);
        sleep(3);
    }
}