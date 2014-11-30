#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include "semaphore.h"

#define true 1
#define READUNIT()  { puts("-- reading"); sleep(10); fflush(0);}
#define WRITEUNIT() { puts("-- writing"); sleep(10); fflush(0);}

#define READ_THREAD_NUM     500
#define WRITE_THREAD_NUM    500

int readcount; // --counter of current readers' number
void* reader();
void* writer();

Semaphore mutex, wsem;

int main() {
    readcount = 0;

    pthread_mutex_init(&lock, NULL);

    mutex = Sem_Create(1, MAX_BLK_THREADS, "mutex");
    wsem = Sem_Create(1, MAX_BLK_THREADS, "wsem");

    pthread_t r[READ_THREAD_NUM], w;
    int i;
    for (i = 0; i < READ_THREAD_NUM; i++)
        pthread_create(&r[i], NULL, reader, NULL);
    pthread_create(&w, NULL, writer, NULL);

    for (i = 0; i < READ_THREAD_NUM; i++)
        pthread_join(r[i], NULL);
    pthread_join(w, NULL);

    return 0;
}

void* reader() {
    int i;
    for (i = 0; i < MAX_LOOP_TIME; i++) {
        P(mutex);
        readcount ++;
        if (readcount == 1) P(wsem);
        V(mutex);

        READUNIT();

        P(mutex);
        readcount --;
        if (readcount == 0) V(wsem);
        V(mutex);
    }
}

void* writer() {
    int i;
    for (i = 0; i < MAX_LOOP_TIME; i++) {
        P(wsem);
        WRITEUNIT();
        V(wsem);
    }
}
