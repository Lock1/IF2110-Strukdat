// ADT Graf
// 13519146 / Fadel Ananda Dotty
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Adjascency List representation in C

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create a graph
struct Graph* createAGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  struct node* newNode = createNode(d);
  newNode->next = graph->adjLists[s];
  graph->adjLists[s] = newNode;

  // Add edge from d to s
  newNode = createNode(s);
  newNode->next = graph->adjLists[d];
  graph->adjLists[d] = newNode;
}

boolean isGraphConnected(struct Graph G, int s, int d){
  struct node* P=G->adjList[s];
  while (P!=NULL){
    if (P->Next==G->adjList[d])
      return true;
    else
      P=P->Next;
  }
  return false;
}

// int main() {
//   struct Graph* graph = createAGraph(4);
//   addEdge(graph, 0, 1);
//   addEdge(graph, 0, 2);
//   addEdge(graph, 0, 3);
//   addEdge(graph, 1, 2);

//   printGraph(graph);

//   return 0;
// }
