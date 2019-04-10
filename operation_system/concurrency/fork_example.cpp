#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int g = 5;

int main() {
    int l = 3;

    pid_t pid = fork();
    if (pid == 0) {
        l += 1;
        printf("child process: pid=%d, g=%d, l=%d\n", pid, g, l);
    } else {
        printf("parent process: pid=%d, g=%d, l=%d\n", pid, g, l);
    }
}