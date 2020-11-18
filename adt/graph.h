#include <stdio.h>
#include <stdlib.h>

#define maxNode 5

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




