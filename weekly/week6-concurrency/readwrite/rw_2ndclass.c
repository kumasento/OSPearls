#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include "semaphore.h"

#define true 1
#define READUNIT()  { puts("-- reading"); sleep(1); }
#define WRITEUNIT() { puts("-- writing"); sleep(1); }

#define READ_THREAD_NUM 100
#define WRITE_THREAD_NUM 100

int readcount, writecount; // --counter of current readers' number
void* reader();
void* writer();

Semaphore mutex1, mutex2, mutex3, wsem, rsem;


int main() {
    readcount = 0;
    writecount = 0;

    pthread_mutex_init(&lock, NULL);

    mutex1 = Sem_Create(1, MAX_BLK_THREADS, "mutex1");
    mutex2 = Sem_Create(1, MAX_BLK_THREADS, "mutex2");
    mutex3 = Sem_Create(1, MAX_BLK_THREADS, "mutex3");
    wsem = Sem_Create(1, MAX_BLK_THREADS, "wsem");
    rsem = Sem_Create(1, MAX_BLK_THREADS, "rsem");

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
        P(mutex3);
        P(rsem);
        P(mutex1);
        readcount ++;
        if (readcount == 1) P(wsem);
        V(mutex1);
        V(rsem);
        V(mutex3);

        READUNIT();

        P(mutex1);
        readcount --;
        if (readcount == 0) V(wsem);
        V(mutex1);
    }
}

void* writer() {
    int i;
    for (i = 0; i < MAX_LOOP_TIME; i++) {
        P(mutex2);
        writecount ++;
        if (writecount == 1) P(rsem);
        V(mutex2);

        P(wsem);
        WRITEUNIT();
        V(wsem);

        P(mutex2);
        writecount --;
        if (writecount == 0) V(rsem);
        V(mutex2);
    }
}
