// ADT Graf
// 13519146 / Fadel Ananda Dotty
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Membuat sebuah node dengan info berupa v
addressGraphNode createNode(int X) {
  addressGraphNode newNode = malloc(sizeof(node));
  Vertex(newNode) = X;
  Next(newNode) = NULL;
  return newNode;
}

// Membuat graph kosong dengan simpul sebanyak vertices
addrGraph createAGraph(int vertices) {
  addrGraph graph = malloc(sizeof(Graph));
  NumVertices(graph) = vertices;

  AdjList(graph) = malloc(vertices * sizeof(addressGraphNode));

  for (int i = 0; i < vertices; i++)
    AdjList(graph)[i] = NULL;

  return graph;
}

// Membuat sisi dari src ke dest
void addEdge(addrGraph graph, int src, int dst) {
  // dari src ke dest
  addressGraphNode newNode = createNode(dst);
  Next(newNode) = AdjList(graph)[src];
  AdjList(graph)[src] = newNode;

  // dari dest ke src
  newNode = createNode(src);
  Next(newNode) = AdjList(graph)[dst];
  AdjList(graph)[dst] = newNode;
}

// Mengeprint graph yang telah dibuat
void printGraph(addrGraph graph) {
  for (int ver = 0; ver < NumVertices(graph); ver++) {
    addressGraphNode temp = AdjList(graph)[ver];
    printf("\n Vertex %d\n: ", ver);
    while (temp) {
      printf("%d -> ", Vertex(temp));
      temp = Next(temp);
    }
    printf("\n");
  }

}

boolean isGraphConnected(addrGraph graph, int src, int dest){
  for (int i=0; i < graph->numVertices; i++){
    addressGraphNode temp = AdjList(graph)[i];
    if(i==src){
      while(temp){
        if (Vertex(temp)==dest)
          return true;
        else
          temp=Next(temp);
      }
    }
  }
  return false;
}
