#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_msg(void *ptr);

int main() {
    pthread_t t1, t2;
    const char *msg1 = "thread 1";
    const char *msg2 = "thread 2";
    int r1, r2;

    r1 = pthread_create(&t1, NULL, print_msg, (void*) msg1);
    r2 = pthread_create(&t2, NULL, print_msg, (void*) msg2);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

void *print_msg(void *ptr) { printf("MSG: %s\n", (char *)ptr); }
