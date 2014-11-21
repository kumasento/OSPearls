
#include <stdlib.h>

#include "semaphore.h"
#include "semaphore_queue.h"

Semaphore Sem_Create( int initCount, int MaxBlkThread ) {
    Semaphore Sem = (Semaphore) malloc(sizeof(struct SemRecord));

    Sem->count  = initCount;                    //-- initialize 
    Sem->q      = CreateQueue(MaxBlkThread);    //-- empty queue

    Sem->m      = (pthread_mutex_t *) 
        malloc(sizeof(pthread_mutex_t) * MaxBlkThread);
    int i;
    for (i = 0; i < MaxBlkThread; i++) 
        pthread_mutex_init(&Sem->m[i], NULL);

    return Sem;
}

// -- this one should not be interleaved
void P(Semaphore sem) {
    pthread_t   tid;
    int         qid;

    pthread_mutex_lock(&lock);
    sem->count --;
    if (sem->count <= 0) {
        pthread_mutex_unlock(&lock);

        // -- inqueue, and lock
        tid = pthread_self();
        qid = Enqueue(tid, sem->q);
        pthread_mutex_lock(&sem->m[qid]);
    } 
    else
        pthread_mutex_unlock(&lock);
}

void V(Semaphore sem) {
    pthread_t   tid;
    int         qid;

    pthread_mutex_lock(&lock);
    sem->count ++;
    if (sem->count <= 0) {
        // -- release one thread
        qid = sem->q->Front;
        tid = Dequeue(sem->q);

        pthread_mutex_unlock(&sem->m[qid]);
    }
    pthread_mutex_unlock(&lock);
}
