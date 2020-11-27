// ADT Graf
// 13519146 / Fadel Ananda Dotty
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

typedef struct node* addrNode;

typedef struct node {
  int vertex;
  addrNode next;
}node;

typedef struct node** LIST;

typedef struct Graph* addrGraph;

typedef struct Graph {
  int numVertices;
  LIST adjLists;
}Graph;

#define Vertex(P) (P)->vertex
#define Next(P) (P)->next
#define NumVertices(G) (G)->numVertices
#define AdjList(G) (G)->adjLists

addrNode createNode(int);
addrGraph createAGraph(int vertices);
void addEdge(addrGraph graph, int src, int dst);
void printGraph(addrGraph graph);
boolean isGraphConnected(addrGraph graph, int src, int dest);

#endif