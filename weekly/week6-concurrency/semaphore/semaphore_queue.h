#ifndef _SEM_QUEUE_H_
#define _SEM_QUEUE_H_

#include <pthread.h>

typedef pthread_t ElemType; 

struct QueueRecord;
typedef struct QueueRecord *Queue;

struct QueueRecord {
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElemType * Array;
};

int     IsEmpty( Queue Q );
int     IsFull( Queue Q );
void    MakeEmpty( Queue Q );
Queue   CreateQueue( int MaxElements );
int    Enqueue( ElemType X, Queue Q );
ElemType Dequeue( Queue Q );

typedef Queue SemQueue;

#endif
