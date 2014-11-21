#include <stdio.h>
#include <stdlib.h>

#include "libthread.h"

#define ARRAYSIZE 1024
#define LOOPTIME 1000

double dtime()
{
    double tseconds = 0.0;
    struct timeval mytime;
    gettimeofday(&mytime,(struct timezone*)0);
    tseconds = (double)(mytime.tv_sec +
    mytime.tv_usec*1.0e-6);
    return( tseconds );
}

typedef struct _args {
    int len;
    int * srcA;
    int * srcB;
    int * res;
} args_type;

int fn(void* args) {
    args_type * thr_args = (args_type*) args;

    int i;
    //printf("len = %d\n", thr_args->len);
    for (i = 0; i < thr_args->len; i++) 
        thr_args->res[i] = 
            thr_args->srcA[i] + 
            thr_args->srcB[i];

    return 1;
}


int main(int argc, char *argv[]) {
    //int ret = runProcedure(proc);
    
    if (argc <= 1) {
        fprintf(stderr, "insufficient parameters");
        exit(1);
    }
    int thread_num = atoi(argv[1]);
    int slicesize = ARRAYSIZE/ thread_num;
    printf("slicesize: %d\n", slicesize);

    int A[ARRAYSIZE];
    int B[ARRAYSIZE];
    int R[ARRAYSIZE];

    int i;
    for (i = 0; i < ARRAYSIZE; i++) {
        A[i] = i * 10+1;
        B[i] = i+1;
        R[i] = 0;
    }

    initEnv();

    for (i = 0; i < thread_num; i++) {
        int *Ai = &A[slicesize * i];
        int *Bi = &B[slicesize * i];
        int *Ri = &R[slicesize * i];

        args_type* args = 
            (args_type*) malloc(sizeof(args_type));
        
        args->srcA = Ai;
        args->srcB = Bi;
        args->res  = Ri;
        args->len  = (i == thread_num-1) ? 
                        (ARRAYSIZE-slicesize * i) : 
                        slicesize;

        procedure_t* proc = 
            initProcedure(&fn, (void *) args);
        
        int tid = thread_fork(proc);
        thread_start(tid);
    }
    
    thread_waitAll();

    for (i = 0; i < ARRAYSIZE; i++)
        if (R[i] != A[i] + B[i])
        printf("id = %d; error! R = %d A + B = %d\n", 
                i,
                R[i],
                A[i] + B[i]);
    return 0;

}

