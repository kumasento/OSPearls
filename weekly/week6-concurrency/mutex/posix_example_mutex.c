#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LOOPCOUNT 10
#define MAXTHREADNUM 100

void *print_counter();
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main() {
    pthread_t t1, t2, t3;
    int r1, r2, r3;

    r1 = pthread_create(&t1, NULL, &print_counter, NULL);
    r2 = pthread_create(&t2, NULL, &print_counter, NULL);
    r3 = pthread_create(&t3, NULL, &print_counter, NULL);

    pthread_join(t2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t3, NULL);

    return 0;
}

void *print_counter() {
    int i = 0;
    for (; i < LOOPCOUNT; i++) {
        pthread_mutex_lock(&m);
        counter ++;
        printf("-- ID = %ld COUNTER = %d\n", pthread_self(), counter);
        pthread_mutex_unlock(&m);
    }
}   
