// ADT Graf
// 13519146 / Fadel Ananda Dotty
#include "../graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  addrGraph graph = createAGraph(4);
  addEdge(graph, 0, 1);
  addEdge(graph, 1, 2);
  addEdge(graph, 2, 3);
  addEdge(graph, 3, 0);

  printGraph(graph);
  printf("\n");

  if (isGraphConnected(graph, 0, 1)) //apabila dua simpul ini terhubung akan mengeprint keterhubungan
    printf("0 1 are connected\n");

  return 0;
}