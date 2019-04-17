#include "helper.h"

void *thread_func(void *idx_ptr) {
    size_t idx = GET_DIX_FR_HEAP(idx_ptr);
    printf("thread of idx %02ld is running.\n", idx);
    return NULL;
}

int main() {
    for (size_t i = 1; i < THREAD_NUM; i++) {
        size_t * idx = PUT_IDX_TO_HEAP(i);
        pthread_create(&threads[i], NULL, thread_func, idx);
    }
    printf("Main Thread Done\n");
    pthread_exit(NULL);
}