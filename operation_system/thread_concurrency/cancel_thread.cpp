#include "helper.h"

void *echo_thread_id(void *idx_ptr) {
    size_t idx = GET_DIX_FR_HEAP(idx_ptr);
    size_t sibling = (idx + 1) % 5;
    while (true) {
        printf("Thread of idx %02ld is running.\n", idx);
        pthread_cancel(threads[sibling]);
        if (sibling == 0) printf("Thread of idx %02d canceled Main Thread.\n", idx, sibling);
        else printf("Thread of idx %02d canceled sibling %02d.\n\n", idx, sibling);
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
    }

    for (size_t i = 1; i < THREAD_NUM; i++) {
        printf("Main Thread is running.\n");
        pthread_cancel(threads[1]);
        printf("Main thread canceled thread of idx %02ld\n\n", i);
        Sleep(1);
    }
}