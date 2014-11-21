#define _GNU_SOURCE // for CLONE_VM
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <signal.h>

#define FIBER_STACK 8192

int a;
void * stack;

int do_something() {
    printf("this is the son, id is %d, a is %d\n", getpid(), ++a);
    free(stack);
    exit(1);
}

int main() {
    void *stack;
    a = 1;
    stack = malloc(FIBER_STACK);
    if (!stack) {
        printf("allocate failed");
        exit(0);
    }
    printf("Creating son thread!\n");
    clone(  &do_something,
            (char*)stack + FIBER_STACK,
            CLONE_VM // in the same mem space
            | CLONE_VFORK, // stall parent process
            0 );
    printf("this is father, pid = %d, a is %d\n", getpid(), a);
    return 0;
}
