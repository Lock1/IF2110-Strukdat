// ADT Graf Variasi MultiList
// 13519146 / Fadel Ananda Dotty
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

typedef struct node* addressGraphNode;

typedef struct node {
  int vertex;
  addressGraphNode next;
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

//Pembuatan node
addressGraphNode createNode(int);
//Pembuatan graph
addrGraph createAGraph(int vertices);
//Pembuatan sisi
void addEdge(addrGraph graph, int src, int dst);
//Pencetakan graph
void printGraph(addrGraph graph);
//Pengecekan dua simpul terhubung
boolean isGraphConnected(addrGraph graph, int src, int dest);

#endif
