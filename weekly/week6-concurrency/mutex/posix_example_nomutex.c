#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXLOOPNUM 100

void *pc();
int c = 0;

int main() {
    pthread_t t1, t2;
    int r1, r2;

    r1 = pthread_create(&t1, NULL, &pc, NULL);
    r2 = pthread_create(&t2, NULL, &pc, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

void *pc() {
    int i = 0; 
    for (i = 0; i < MAXLOOPNUM; i++) {
        // no mutex here!
        printf("-- COUNT: %d\n", c);
        c ++;
        // no mutex here!
    }

}
