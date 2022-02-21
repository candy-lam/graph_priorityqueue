/* DisjSet.h */
#ifndef DISJSET_H
#define DISJSET_H

typedef struct DisjSetCDT *DisjSetADT;
DisjSetADT NewDisjointSet(void);
void SetUnion(DisjSetADT, int, int);
int Find(int, DisjSetADT);

#endif // DISJSET_H
