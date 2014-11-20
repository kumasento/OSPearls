#include <stdio.h>
#include <stdlib.h>

#define LINKLEN 100

/*
typedef struct LinkNode{
    int val;
    struct LinkNode* next;
} Node;
*/

int main(int argc, char *argv[]) {
    /*
    Node* head = (Node*) malloc(sizeof(Node));
    head->val = -1;

    puts("Initializing ...");
    int i;
    Node *t = head;
    for (i = 0; i < LINKLEN; i++) {
        Node *tmp = (Node *) malloc(sizeof(Node));
        tmp->val = i;
        t->next = tmp;
        t = tmp;
    }
    puts("Testing ...");
    t = head;
    for (i = 0; i < LINKLEN *10000; i++) {
        printf("%d\n", t->val);
        t = t->next;
    }
    */
    int *a;
    a[10] = 1;
    return 0;
}
