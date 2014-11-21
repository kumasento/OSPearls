#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define MAXL 100

pthread_mutex_t lock;

int count;
void *func(void *args) {
    int i;
    for (i = 0; i < MAXL; i++) {
        pthread_mutex_lock(&lock);
        count ++;
        printf("-- count: %d\n", count);
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}
int main() {

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, func, NULL);
    pthread_create(&tid2, NULL, func, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
