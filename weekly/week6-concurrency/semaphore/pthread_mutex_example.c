#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define MAXL 100

struct foo {
    int             f_count;
    pthread_mutex_t f_lock;
};

struct foo * 
foo_alloc(void) {
    struct foo * fp;
    if ((fp = malloc(sizeof(struct foo))) != NULL) {
        fp->f_count = 1;
        if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
            free(fp);
            return NULL;
        }
    }
    return fp;
}

void foo_hold(struct foo *fp) {
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count ++;
    printf("-- fp->count: %d\n", fp->f_count);
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp) {
    pthread_mutex_lock(&fp->f_lock);
    if (--fp->f_count == 0) {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }
    else {
        pthread_mutex_unlock(&fp->f_lock);
    }
}

void* thread_function(void *arg) {
    printf("-- Thread Start!\n");

    int i;
    struct foo *fp = (struct foo *) arg;
    for (i = 0; i < MAXL; i++) 
        foo_hold(fp);

    return NULL;
}

int main() {
    pthread_t   tid1, tid2;
    
    struct foo *fp = foo_alloc();
    pthread_create(&tid1, NULL, thread_function, fp);
    pthread_create(&tid2, NULL, thread_function, fp);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
