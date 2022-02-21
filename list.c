#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

typedef struct listCDT *listADT;

struct listCDT {
    listElementT h;
    listADT t;
};

listADT EmptyList() {
    return((listADT)NULL);
}

listADT Cons(listElementT h1, listADT t1) {
    listADT list = (listADT) malloc(sizeof(*list));
    list->h = h1;
    list->t = t1;
    return (list);
}

listElementT Head(listADT list) {
    if (ListIsEmpty(list))
        exit(EXIT_FAILURE);
    return (list->h);
}

listADT Tail(listADT list) {
    if (ListIsEmpty(list))
        exit(EXIT_FAILURE);
    return (list->t);
}

int ListIsEmpty(listADT list) {
    return (list == NULL);
}
