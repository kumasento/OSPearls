
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "semaphore.h"

#define MAX_BLK_THREADS 100 
#define MAX_LOOP_NUMBER 100

Semaphore mutex;

int count;
void *func(void *args) {
    int i;
    for (i = 0; i < MAX_LOOP_NUMBER; i++) {
        P(mutex);
        count ++;
        printf("-- count : %d\n", count);
        V(mutex);
    }

    return NULL;
}

int main() {
    pthread_mutex_init(&lock, NULL);
    
    mutex = Sem_Create(1,MAX_BLK_THREADS);

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, func, NULL);
    pthread_create(&tid2, NULL, func, NULL);
    pthread_create(&tid3, NULL, func, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    return 0;
}
