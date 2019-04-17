#include "helper.h"

void *echo_thread_id(void * idx_ptr) {
    while (true) {
        size_t idx = GET_DIX_FR_HEAP(idx_ptr);
        printf("Thread of idx %02ld is running.\n", idx);
        pthread_exit(NULL);
    }
}


int main() {
    pthread_t tid = pthread_self();
    threads[0] = tid;
    for (size_t i = 1; i < THREAD_NUM; i++) {
        size_t* idx = PUT_IDX_TO_HEAP(i);
        pthread_create(&threads[i], NULL, echo_thread_id, idx);
    }
    Sleep(1);
}