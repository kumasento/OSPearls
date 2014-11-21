#include <stdio.h>
#include <stdlib.h>

#include "libthread.h"

typedef struct _args {
    int id;
} args_type;

int fn(void* args) {
    args_type * thr_args = (args_type*) args;
    printf("%d\n", thr_args->id);
    return 1;
}

int main() {
    args_type* args = (args_type*) malloc(sizeof(args_type));
    args->id = 10;

    procedure_t* proc = initProcedure(&fn, (void *) args);
    int ret = runProcedure(proc);
    
    printf("return value is %d\n", ret);
    return 0;

}

