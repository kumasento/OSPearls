#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) 
        exit(0); // exit immediately, before the parent one terminates
    else
        sleep(60);
    return 0;
}
