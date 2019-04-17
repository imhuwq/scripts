#include <cstring>
#include "helper.h"

#define PTHREAD_JOIN(tid) int r = pthread_join((tid), NULL); \
                          if(r != 0) printf("failed to join thread: %02d %s\n", r, strerror(errno))

void *thread_func(void *idx_ptr) {
    size_t idx = GET_DIX_FR_HEAP(idx_ptr);
    if (idx > 1) {
        pthread_join(threads[idx - 1], NULL);
        printf("thread of idx %02ld waited %02ld.\n", idx, idx - 1);
    }
    printf("thread of idx %02ld is running.\n", idx);
    return NULL;
}

int main() {
    for (size_t i = 1; i < THREAD_NUM; i++) {
        size_t *idx = PUT_IDX_TO_HEAP(i);
        pthread_create(&threads[i], NULL, thread_func, idx);
    }
    Sleep(2);
    PTHREAD_JOIN(threads[4]);
    printf("Thread Main waited %02ld.\n", 4l);
    printf("Thread Main Done\n");
}