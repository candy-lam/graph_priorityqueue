/* graph.c */
#include "graph.h"
#include "list.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#define MAX_N 100 /* Possible nodes are node 0, node 1, ..., node 99. */

struct GraphCDT {
    float W[MAX_N*(MAX_N+1)/2];
    bool NodeExists[MAX_N];
};

GraphADT EmptyGraph(void){                 /* returns an empty undirected graph */
    GraphADT G;
    G = (GraphADT)malloc(sizeof(*G));
    for (int i = 0; i < MAX_N; i++){
        G->NodeExists[i] = false;
    }
    return G;
}

bool GraphIsEmpty(GraphADT G){                /* returns whether graph is empty */
    for (int i = 0; i < MAX_N; i++){
        if (G->NodeExists[i] == true)
            return false;
    }
    return true;
}

void AddNode(GraphADT G, Node n){               /* add a node */
    G->NodeExists[n] = true;
}

bool NodeExists(GraphADT G, Node n){/* returns whether the node exists */
    if (GraphIsEmpty(G)) exit(EXIT_FAILURE);
    return (G->NodeExists[n]);
}

listADT AdjacentNodes(GraphADT G, Node n){      /* returns a list of adjacent nodes */
    if (!(G->NodeExists[n])) return NULL;
    listADT list;
    list = EmptyList();
    for (int i = 0; i < MAX_N; i++){
        if (ArcExists(G, i, n))
            list = Cons(i, list);
    }
    return list;
}

int Degree(GraphADT G, Node n){                 /* returns the degree of node */
    if (!NodeExists(G, n)) return -1;
    int count = 0;                              /* default as isolated node*/
    for (int i = 0; i < MAX_N; i++){
        if (ArcExists(G, i, n))                 /* if arc exists, degree + 1*/
            count++;
    }
    return count;
}

void AddArc(GraphADT G, Node n1, Node n2, float w){/* add an arc *//* note that the last argument is the weight */
    if (!NodeExists(G, n1)) return;
    if (!NodeExists(G, n2)) return;
    int temp = n1;  // swap n1 and n2 if n1 > n2
    if (n1 > n2){
        n1 = n2;
        n2 = temp;
    }
    temp = n2 + n1 * MAX_N - n1* (n1 + 1) / 2;
    G->W[temp] = w;
    //printf("Arc %d%d with weight %0.0f added [%d]\n", n1, n2, w, temp);
}

float ArcWeight(GraphADT G, Node n1, Node n2){      /* returns the weight of an arc, possibly INFINITY */
    if (!NodeExists(G, n1)) return 0;
    if (!NodeExists(G, n2)) return 0;
    float weight;
    int temp = n1;  // swap n1 and n2 if n1 > n2
    if (n1 > n2){
        n1 = n2;
        n2 = temp;
    }
    if (ArcExists(G, n1, n2))
        return G->W[ArctoIndex(G, n1, n2)];
    else return 0;
}

bool ArcExists(GraphADT G, Node n1, Node n2){       /* returns whether the arc exists */
    if (!NodeExists(G, n1)) return false;
    if (!NodeExists(G, n2)) return false;
    int temp = n1;
    if (n1 > n2){
        n1 = n2;
        n2 = temp;
    }
    temp = n2 + n1 * MAX_N - n1* (n1 + 1) / 2;
    if (G->W[temp] == 0)
        return false;
    return true;
}

void PrintAllNodes(GraphADT G){               /* prints all existing nodes */
    if (GraphIsEmpty(G)) exit(EXIT_FAILURE);
    for (int i = 0; i <MAX_N; i++){
        if (NodeExists(G, i))
            printf("%d \n", i);
    }
}

void PrintAllArcs(GraphADT G){                /* prints all existing arcs */
    if (GraphIsEmpty(G)) exit(EXIT_FAILURE);
    int count;
    for (int i = 0; i < MAX_N; i++){
        count = 0;
        for (int j = i + 1; j < MAX_N ;j++){
            //printf("Check %d %d\n", i, j);
            if (ArcExists(G, i, j)){
                printf("(%d,%d) %0.0f\n", i, j, G->W[ArctoIndex(G, i, j)]);
                count++;
            }
            if (count == Degree(G, i)) break; //escape loop when all arc of i was printed
        }
    }
}

int ArctoIndex(GraphADT G, Node i, Node j) {    /*input arc return x in W[x]*/
    if (!ArcExists(G, i, j)) exit(EXIT_FAILURE);
    return j + i*MAX_N - i*(i+1)/2;
}

void IndextoArcNodes(GraphADT G, int x, Node* i, Node* j) { /*Input x return arc*/
    int m = 1; int n;
    int x1; while (x >= (x1 = m * MAX_N - m * (m - 1) / 2)) m++;
    m--; n = MAX_N + x - x1;
    (*i) = m; (*j) = n;
    /* The arc is (m,n), or ((*i),(*j))--whether the arc exists is not checked! */
}
