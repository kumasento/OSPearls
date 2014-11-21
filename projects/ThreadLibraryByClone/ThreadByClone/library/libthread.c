#define _GNU_SOURCE
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <stdio.h>

#include "libthread.h"

procedure_t* initProcedure(int (*fn) (void*), void *args) {
    procedure_t * new_proc = 
        (procedure_t *) malloc(sizeof(procedure_t));
    new_proc->function = fn;
    new_proc->arguments= args;

    return new_proc;
}
int runProcedure(procedure_t* proc) { 
    return proc->function(proc->arguments); 
}

/// About thread implemention

// global variables
thread_t * thread_queue[MAX_THREAD];
int thread_queue_length = 0;
pid_t shared_parent;

void initEnv() {
    shared_parent = getpid();
    int i;
    for (i = 0; i < MAX_THREAD; i++) 
        thread_queue[i] = NULL;

    printf("Environment Setup! parent Id = %5d ...\n", 
            shared_parent);
}

thread_id thread_fork(procedure_t* proc) {

    stack_pointer stack = malloc(STACK_SIZE);
    stack_pointer stack_top;
    if (stack == NULL) 
        return -1;

    if (thread_queue_length == MAX_THREAD) {
        fprintf(stderr, "Cant't create any more!");
        return -1;
    }

    thread_queue[thread_queue_length] = 
        (thread_t *) malloc(sizeof(thread_t));
    thread_queue[thread_queue_length]->stack = stack;
    thread_queue[thread_queue_length]->proc = proc;
    thread_queue[thread_queue_length]->id = -1;
    
    int idx = thread_queue_length;
    thread_queue_length ++;

    printf("new thread pushed! thread queue length is %3d now\n", 
            thread_queue_length);
    return idx; 
}

thread_id thread_start(int tid) {
    thread_t *cur = thread_queue[tid];
    
    procedure_t *proc       = cur->proc;
    stack_pointer stack     = cur->stack;
    stack_pointer stack_top = stack + STACK_SIZE;

    cur->id = clone(proc->function, 
                    stack_top,
                    FLAGS,
                    proc->arguments);
    
    printf("thread id %d is running!\n", cur->id);
    return cur->id;
}

void thread_waitAll() {

    int thread_reaped = 0;
    while (thread_reaped < thread_queue_length) {
        int status;
        pid_t pid = wait(&status);
        if (pid == -1)
            break;

        int i;
        for (i = 0; i < thread_queue_length; i++)
            if (thread_queue[i]->id == pid) {
                printf("%d quited!\n", pid);
                thread_reaped ++;
                //free(thread_queue[i]->stack);
                //free(thread_queue[i]->proc);
                break;
            }
    }

    thread_queue_length = 0;
    puts("thread queue cleaned!");
}
