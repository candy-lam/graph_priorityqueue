/* graph.h */
#ifndef GRAPH_H
#define GRAPH_H
#include "list.h"
#include <stdbool.h>

typedef struct GraphCDT * GraphADT;
typedef int Node;

GraphADT EmptyGraph(void);                  /* returns an empty undirected graph */
bool GraphIsEmpty(GraphADT);                /* returns whether graph is empty */

void AddNode(GraphADT, Node);               /* add a node */
bool NodeExists(GraphADT, Node);            /* returns whether the node exists */
listADT AdjacentNodes(GraphADT, Node);      /* returns a list of adjacent nodes */
int Degree(GraphADT, Node);                 /* returns the degree of node */
void AddArc(GraphADT, Node, Node, float);
                                            /* add an arc */
                                            /* note that the last argument is the weight */

float ArcWeight(GraphADT, Node, Node);      /* returns the weight of an arc, possibly INFINITY */
bool ArcExists(GraphADT, Node, Node);       /* returns whether the arc exists */

void PrintAllNodes(GraphADT);               /* prints all existing nodes */
void PrintAllArcs(GraphADT);                /* prints all existing arcs */

int ArctoIndex(GraphADT, Node, Node);       /* see below */
void IndextoArcNodes(GraphADT, int, Node*, Node*);
                                            /* see below */


#endif // GRAPH_H
