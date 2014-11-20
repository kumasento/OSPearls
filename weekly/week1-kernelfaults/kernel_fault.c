#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
#ifdef DRNULL
    puts("Dereferencing NULL pointer ...");
    char *null_pointer = malloc(sizeof(char));
    free(null_pointer);
    free(null_pointer);
#endif
#ifdef DIVZERO
    puts("Please Enter Zero!");
    int preset_integer = 10;
    int zero_value; scanf("%d", &zero_value);
    int cal = preset_integer / zero_value;
    printf("%f\n", cal); // Here the fault happens
#endif
#ifdef UNDEFINED
    puts("Undefined Instructions ...");
    typedef void (*Exception)(void);
    static unsigned long illegalOpcode = 0;
    Exception e = (Exception)&illegalOpcode;
    e();
#endif
    return 0;
}
