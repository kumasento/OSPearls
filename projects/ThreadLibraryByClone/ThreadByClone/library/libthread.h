#ifndef _LIB_THREAD_H_
#define _LIB_THREAD_H_

#define errExit(msg) do {perror(msg); exit(EXIT_FAILURE);} while (0)

#include <signal.h>

typedef struct _procedure_t {
    int (*function) (void *);
    void *arguments;
} procedure_t;

procedure_t* initProcedure(int (*fn) (void*), void *args); 
int runProcedure(procedure_t* proc);

#define STACK_SIZE 8196 // 8MB stack
// Here create thread only clone VM
#define FLAGS (CLONE_VM | SIGCHLD)

typedef int thread_id;
typedef char * stack_pointer;

typedef struct _thread_t {
    procedure_t * proc;
    thread_id id;
    stack_pointer stack;
} thread_t;

#define MAX_THREAD 100

thread_id thread_fork(procedure_t* proc);
int thread_start(int tid);
void thread_waitAll();

#endif
