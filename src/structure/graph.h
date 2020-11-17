#ifndef graph_H
#define graph_H

typedef struct tnode *address;
typedef struct tnode{
    int info;
    address *next;
} node;
typedef struct {
    address last;
};

void ReadGraph(address ad[], int nbNode);
void PrintGraph(address ad[], int nbNode);

#endif