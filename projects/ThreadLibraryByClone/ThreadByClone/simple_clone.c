#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h> // import clone function
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <malloc.h>

#define THREAD_STACK_SPACE 1024 * 1024

// clone function should return value/
int clone_function(void *args) {
    fprintf(stdout, "Calling from cloned thread ...\n");
    return 0;
}

int main() {
    pid_t pid;
    char * thread_stack = (char *) malloc(THREAD_STACK_SPACE);
    char * thread_stack_top;
    if (thread_stack == 0) {
        perror("malloc error: couldn't allocate space");
        exit(1);
    }

    puts("Creating ...");

    thread_stack_top = thread_stack + THREAD_STACK_SPACE;
    pid = clone(&clone_function, 
                thread_stack_top,
                SIGCHLD,
                0);

    if (pid == -1) {
        perror("clone error");
        exit(1);
    }
    printf("clone() = %ld\n", (long) pid);

    sleep(1);
    pid = waitpid(pid, 0, 0);
    if (pid == -1) {
        perror("waitpid error");
        exit(1);
    }

    free(thread_stack);
    puts("Returned and freed");

    return 0;
}
