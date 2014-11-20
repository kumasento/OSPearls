#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXTHREADNUM 1024
#define MAXLOOPNUM 100
#define true 1
#define false 0
#define bool int

typedef struct { int id; } tparam;
void *ps(void * p);
int c = 0;

int turn[MAXTHREADNUM];
char rd[MAXTHREADNUM];
int N = 2;

int main(int argc, char *argv[]) {
    if (argc > 1)
        N = atoi(argv[1]);
    int i;
    pthread_t tarr[MAXTHREADNUM];
    tparam tp[MAXTHREADNUM];
    for (i = 0; i < N; i++) {
        tp[i].id = i;
        pthread_create(&tarr[i], NULL, &ps, (void *) &tp[i]);
    }
    // MUTEX init
    for (i = 0; i < N; i++) turn[i] = 0;
    for (i = 0; i < N; i++) rd[i] = 0;

    for (i = 0; i < N; i++) pthread_join(tarr[i], NULL);
    return 0;
}

void *ps(void *p) {
    int id = ((tparam*)p)->id;
    int i, j; 
    for (i = 0; i < MAXLOOPNUM; i++) {
        for (j = 1; j < N; j++) {
            rd[id] = j;
            turn[j] = id;
            int l, k;
            do {
                l = 1;
                for (k = 0; k < N; k ++) 
                    if (k != id) 
                        l &= (rd[k] < j);
            } while (!l && turn[j] == id);
        }
        // CRITICAL SECTION: ENTER

        c ++;
        printf("-- COUNT: %d\n", c);

        rd[id] = 0;
        // CRITICAL SECTION: EXIT
        //
    }
}
