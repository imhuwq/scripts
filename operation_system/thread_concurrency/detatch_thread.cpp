#include "helper.h"
#include <cstring>

#define THREAD_DETACH(tid) int r = pthread_detach((tid)); \
                           if (r != 0) printf("failed to detach thread: %d, %s.\n", r, strerror(errno))

void *echo_thread_id(void *idx_ptr) {
    size_t idx = GET_DIX_FR_HEAP(idx_ptr);

    while (true) {
        printf("Thread of idx %02ld is running.\n", idx);
        Sleep(1);
    }
    return NULL;
}


int main() {
    pthread_t tid = pthread_self();
    threads[0] = tid;
    for (size_t i = 1; i < THREAD_NUM; i++) {
        size_t *idx = PUT_IDX_TO_HEAP(i);
        pthread_create(&threads[i], NULL, echo_thread_id, idx);
        THREAD_DETACH(threads[i]);
        printf("Main Thread make thread of idx %02ld detached.\n", i);
    }

    while (true) {
        printf("Main Thread is running.\n\n");
        Sleep(1);
    }
}