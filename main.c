/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "priorityQueue.h"
#include "DisjSet.h"
#define MAX_N 100

typedef struct arc arcT;

struct arc{
    Node m;
    Node n;
    float w;
};


GraphADT mspK(GraphADT G){
    bool used[MAX_N*(MAX_N+1)/2] = {false};
    arcT a;
    priorityQueueADT pQ = EmptyPriorityQueue();
    GraphADT STree = EmptyGraph();
    int count;
    for (int i = 0; i < MAX_N; i++){
        count = 0;
        for (int j = i + 1; j < MAX_N; j++){
            if (ArcExists(G, i, j)){
                a.m = i;
                a.n = j;
                a.w = ArcWeight(G, i, j);
                PriorityEnqueue(pQ, a.w);
                count++;
                //printf("Enqueue: %d%d %0.0f\n", a.m, a.n, a.w);
            }
            if (count == Degree(G, i)) break;   //escape loop when all arc of i was queued
        }
    }

    DisjSetADT ds = NewDisjointSet();
    float temp;
    bool discard = false;
    while (!PriorityQueueIsEmpty(pQ)){
        discard = false;
        a.w = PriorityDequeue(pQ);
        for (int i = 0; i < MAX_N; i++){
            for (int j = i+1; j < MAX_N; j++){
                temp = ArcWeight(G, i, j);
                if (temp == 0) continue;
                if (temp == a.w){
                    if (!used[ArctoIndex(G, i, j)]){
                        a.m = i;
                        a.n = j;
                    }
                }
            }
        }
        used[ArctoIndex(G, a.m, a.n)] = true;

        //printf("Dequeue: %d%d w-%0.0f\n",a.m ,a.n ,a.w);

        //printf("Find(a.m, ds): %d\n", Find(a.m, ds));
        //printf("Find(a.n, ds): %d\n", Find(a.n, ds));

        if (!GraphIsEmpty(STree)){
            if (Find(a.m+1, ds) == a.m+1 && Find(a.n+1, ds) == a.n+1){
                discard = true;
            }
        }

        if (Find(a.m+1, ds) == Find(a.n+1, ds)){
            //printf("%d%d discard\n\n", a.m, a.n);
            discard = true;
        }

        if (discard == false){
            SetUnion(ds, a.m+1, a.n+1);
            AddNode(STree, a.m);
            AddNode(STree, a.n);
            AddArc(STree, a.m, a.n, a.w);
        }
    }

    return STree;
}


int main()
{
    FILE *datafile = fopen("GraphData.dat", "r");
    if (datafile == NULL){
        printf("File not found.\n");
        return 0;
    }   //if no GraphData.dat found, end the program

    char operation, line[100];
    int m, n, w, count;
    GraphADT G = EmptyGraph();

    while (fgets(line, 100, datafile) != NULL){ //Read character one by one
        operation = 'e';
        m = -1;
        n = -1;
        w = -1;
        count = 0;
        while (line[0] == ' '){
            line[0] = line[count+1];
            line[count+1] = ' ';
            count++;
        }
        sscanf(line, "%c %d %d %d", &operation, &m, &n, &w);
        //printf("%c %d %d %d\n", operation, m, n, w);

        if (operation == 'n'){
            AddNode(G, m);
        }
        else if (operation == 'a'){
            AddArc(G, m, n, w);
        }

    }

    fclose(datafile);
    printf("========================Task1========================\n");
    PrintAllNodes(G);
    printf("\n");
    PrintAllArcs(G);
    printf("\n\n");

    printf("========================Task2========================\n");
    GraphADT STree = mspK(G);
    PrintAllNodes(STree);
    printf("\n");
    PrintAllArcs(STree);
    printf("\n\n");

    printf("-----End of Program-----\n");
    return 0;
}
