// ADT Graf
// 13519146 / Fadel Ananda Dotty
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

#define maxNode 4

typedef struct Node *address;

typedef struct Node{
    int vertexNum;
    address next;
}Node;

typedef struct List{
    address head;
}List;

List *adjlist[maxNode]={0};

void addNode(int s, int d);

void printList();

void linkMapGraph();

boolean isGraphConnected(int src, int dest);