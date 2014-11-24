
#include <stdio.h>
#include <stdlib.h>

#include "semaphore.h"
#include "semaphore_queue.h"

Semaphore Sem_Create( int initCount, int MaxBlkThread, char* name ) {
    Semaphore Sem = (Semaphore) malloc(sizeof(struct SemRecord));

    Sem->count  = initCount;                    //-- initialize 
    Sem->q      = CreateQueue(MaxBlkThread);    //-- empty queue
    Sem->name   = name;

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
    //printf("-- P[%s]: START\n", sem->name);
    //printf("-- P[%s]: count: %d\n", sem->name, sem->count);
    sem->count --;
    if (sem->count <= 0) {
        pthread_mutex_unlock(&lock);

        // -- inqueue, and lock
        tid = pthread_self();
        qid = Enqueue(tid, sem->q);
        //printf("-- P[%s]: END\n", sem->name);
        pthread_mutex_lock(&sem->m[qid]);
    } 
    else {
        //printf("-- P[%s]: END\n", sem->name);
        pthread_mutex_unlock(&lock);
    }
}

void V(Semaphore sem) {
    pthread_t   tid;
    int         qid;

    pthread_mutex_lock(&lock);
    //printf("-- V[%s]: START\n", sem->name);
    //printf("-- V[%s]: count: %d\n", sem->name, sem->count);
    sem->count ++;
    if (sem->count <= 0) {
        // -- release one thread
        qid = sem->q->Front;
        // -- if there's nothing blocked
        // -- 
        if (sem->q->Size > 0) {
            tid = Dequeue(sem->q);

            pthread_mutex_unlock(&sem->m[qid]);
        }
    }
    //printf("-- V[%s]: END\n", sem->name);
    pthread_mutex_unlock(&lock);
}
