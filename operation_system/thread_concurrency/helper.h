#ifndef SCRIPTS_C_HELPER_H
#define SCRIPTS_C_HELPER_H

#include <cstdio>
#include <thread>
#include <zconf.h>

const int thread_num = 5;
#define THREAD_NUM thread_num
pthread_t threads[THREAD_NUM];

#define PUT_IDX_TO_HEAP(i) (size_t *)malloc(sizeof(size_t)); *idx = (i)
#define GET_DIX_FR_HEAP(ptr) *(size_t*)ptr

void Sleep(size_t scs) {
    size_t left_scs = scs;
    while (left_scs) {
        left_scs = sleep(left_scs);
    }
}

#endif //SCRIPTS_C_HELPER_H
