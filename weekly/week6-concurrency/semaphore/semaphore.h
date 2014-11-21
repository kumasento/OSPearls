#ifndef _SEM_H_
#define _SEM_H_

#include <pthread.h>

#include "semaphore_queue.h"

struct SemRecord;
typedef struct SemRecord * Semaphore;

Semaphore Sem_Create( int initCount, int MaxBlkThread );
void P(Semaphore sem);
void V(Semaphore sem);

struct SemRecord {
    int count;
    pthread_mutex_t* m; // -- used to create block
    SemQueue q;
};

// -- prevent interleaving in P() & V()
// -- for all P() and V() functions, not the ones related to sem
//
pthread_mutex_t lock;

#endif
