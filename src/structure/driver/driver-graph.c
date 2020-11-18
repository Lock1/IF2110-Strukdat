// ADT Graf
// 13519146 / Fadel Ananda Dotty
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void main(){
    for (int i=0; i<maxNode; i++){
        adjlist[i]=(List*)malloc(sizeof(List));
        adjlist[i]->head=NULL;
    }
addNode(1,1);
addNode(2,1);
addNode(2,2);
printList();
getch();
}
