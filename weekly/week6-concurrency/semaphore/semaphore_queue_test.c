
#include <stdio.h>

#include "semaphore_queue.h"

void *func(void *arg) { return NULL; }

int main() {

    const int maxElems = 100;

    Queue q = CreateQueue(maxElems);
    
    printf("-- IsEmpty: %d\n", IsEmpty(q));
    printf("-- IsFull: %d\n", IsFull(q));

    int i;
    for (i = 0; i < maxElems; i++) { 
        pthread_t tid;
        pthread_create(&tid, NULL, func, NULL); 
        Enqueue(tid, q);
    }
    
    for (i = 0; i < maxElems; i++) 
        printf("-- Dequeue: %u\n",(unsigned int) Dequeue(q));

    return 0;
}
