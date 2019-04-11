/*
 * 信号处理函数可以被打断，但和被打断的系统调用不同，被打断的信号处理函数会接着执行，而后者会返回错误(或者 restart)。
 */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <zconf.h>

int s1 = 0;
int s2 = 0;
int pid = 0;

void sig_user1_handler(int) {
    kill(pid, SIGABRT);
    s1 = 1;
    exit(s1 + s2);
}

void sig_user2_handler(int) {
    s2 = 2;
}

int main() {
    signal(SIGINT, sig_user1_handler);
    signal(SIGABRT, sig_user2_handler);
    pid = getpid();

    while (true) {}
}