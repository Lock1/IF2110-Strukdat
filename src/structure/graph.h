// ADT Graf
// 13519146 / Fadel Ananda Dotty
#ifndef graph_H
#define graph_H

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "listlinear.h"

struct node {
  int vertex;
  struct node* next;
};
struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
};

#endif