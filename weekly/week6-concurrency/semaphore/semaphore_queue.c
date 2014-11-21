#include <stdio.h>
#include <stdlib.h>

#include "semaphore_queue.h"

int IsEmpty(Queue Q) { return Q->Size == 0; }

int IsFull(Queue Q) { return Q->Size == Q->Capacity; }

void MakeEmpty(Queue Q) { 
    Q->Size     = 0;
    Q->Front    = 1;
    Q->Rear     = 0;
}

Queue CreateQueue( int MaxElements ) {
    Queue Q = (Queue) malloc(sizeof(struct QueueRecord));
    
    Q->Array    = (ElemType*) malloc(sizeof(MaxElements));
    Q->Capacity = MaxElements;
    
    MakeEmpty(Q);

    return Q;
}

int Enqueue( ElemType X, Queue Q ) {
    if (IsFull(Q)) {
        fprintf(stderr, "ERROR: Q Full\n");
        exit(1);
    }

    Q->Size ++;
    Q->Rear = (Q->Rear + 1) % Q->Capacity;
    Q->Array[Q->Rear] = X;

    return Q->Rear;
}

ElemType Dequeue( Queue Q ) {
    if (IsEmpty(Q)) {
        fprintf(stderr, "ERROR: Q Empty\n");
        exit(1);
    }

    ElemType ret = Q->Array[Q->Front];
    Q->Size --;
    Q->Front = (Q->Front + 1) % Q->Capacity;
    
    return ret;
}
