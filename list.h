/* list.h */
#ifndef LIST_H
#define LIST_H

typedef struct listCDT *listADT;
typedef int listElementT;
listADT EmptyList(void);
listADT Cons(listElementT, listADT);
listElementT Head(listADT);
listADT Tail(listADT);
int ListIsEmpty(listADT);


#endif
