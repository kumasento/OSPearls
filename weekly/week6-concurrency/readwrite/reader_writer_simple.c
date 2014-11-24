#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "semaphore.h"

#define MAX_BUF_SIZE    100
#define MAX_BLK_THREADS 1000
#define MAX_LOOP_TIME   1000

// -- without mutex
int produce();
void consume(int item);

// -- with semaphore
void insert(int pos, int item);
int take(int pos);

// -- general function
void *reader(void *args);
void *writer(void *args);

int buf[MAX_BUF_SIZE];
int product = 0;
Semaphore empty, full, mutex;

int main() {

    pthread_mutex_init(&lock, NULL);

    empty   = Sem_Create(MAX_BUF_SIZE, MAX_BLK_THREADS, "empty");
    full    = Sem_Create(0, MAX_BLK_THREADS, "full");
    mutex   = Sem_Create(1, MAX_BLK_THREADS, "mutex");

    // -- t1: reader t2: writer
    pthread_t t1, t2;
    pthread_create(&t1, NULL, reader, NULL);
    pthread_create(&t2, NULL, writer, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

int produce() { return product++; }
void consume(int item) { printf("-- consumed: %d\n", item); }

void insert(int pos, int item) { buf[pos] = item; }
int take(int pos) { return buf[pos]; }

void *reader(void *args) {
    int pos = 0, item;
    int i;
    for (i = 0; i < MAX_LOOP_TIME; i++) {
        pos = (pos + 1) % MAX_BUF_SIZE;
        item = produce();
        puts("-- before reader block:");
        P(empty);
        P(mutex);
        insert(pos, item);
        V(mutex);
        V(full);
    }
    return NULL;
}

void *writer(void *args) {
    int pos = 0, item;
    int i;
    for (i = 0; i < MAX_LOOP_TIME; i++) {
        pos = (pos + 1) % MAX_BUF_SIZE;
        puts("-- before writer block:");
        P(full);
        P(mutex);
        item = take(pos);
        V(mutex);
        V(empty);
        consume(item);
    }
    return NULL;
}
