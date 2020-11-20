// ADT Graf
// 13519146 / Fadel Ananda Dotty
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

#define maxgraphNode 4

typedef struct graphNode *graphAddress;

typedef struct graphNode{
    int vertexNum;
    graphAddress next;
}graphNode;

typedef struct graphList{
    graphAddress head;
}graphList;

graphList *adjgraphList[maxgraphNode];

void addgraphNode(int s, int d);

void printgraphList();

void linkMapGraph();

boolean isGraphConnected(int src, int dest);
