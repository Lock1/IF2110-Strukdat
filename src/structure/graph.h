// Driver linked list
// 13519146 / Fadel Ananda Dotty
#ifndef graph_H
#define graph_H

typedef struct tnode *address;
typedef struct tnode {
    int info;
    address next;
} node;
typedef struct g {
    address last;
} graph;

void ReadGraph(address ad[], int nbNode);
void PrintGraph(address ad[], int nbNode);

#endif
