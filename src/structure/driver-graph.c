#include "graph.h"
#include <stdio.h>
#include <stlib.h>

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