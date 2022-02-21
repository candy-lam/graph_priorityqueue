/* DisjSet.c */
#include <stdlib.h>
#include <stdbool.h>
#include "DisjSet.h"

struct DisjSetCDT {
    int class[101];
};

DisjSetADT NewDisjointSet() {
    DisjSetADT ds;
    ds = (DisjSetADT) malloc(sizeof(*ds));
    for (int i=100; i>0; i--) ds->class[i] = -1;
        return ds;
}

int Find(int X, DisjSetADT S) {
    if (S->class[X] <= 0) return X;
    return Find(S->class[X], S);
}

void SetUnion(DisjSetADT S, int X1, int X2) {
    int R1, R2;
    R1 = Find(X1, S);
    R2 = Find(X2, S);
    if (R1 != R2) {
        if (-(S->class[R1]) < -(S->class[R2]))
        /* R2 is deeper */
        S->class[R1] = R2;
        else {
            if (S->class[R1]==S->class[R2])
                (S->class[R1])--;
            S->class[R2] = R1;
        }
    }
}
