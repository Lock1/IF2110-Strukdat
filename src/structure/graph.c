// ADT Graf
// 13519146 / Fadel Ananda Dotty
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void addgraphNode(int s, int d){
    graphAddress dest, temp, src;
    if(adjgraphList[s]->head==NULL){
        src=(graphAddress)malloc(sizeof(graphNode));
        src->vertexNum=s;
        src->next=NULL;
        adjgraphList[s]->head=src;
    }
    dest=(graphAddress)malloc(sizeof(graphNode));
    dest->vertexNum=d;
    dest->next=NULL;
    temp=adjgraphList[s]->head;
    while (temp->next!=NULL)
        temp=temp->next;
    temp->next=dest;
}

void printgraphList(){
    for(int i=0; i<maxgraphNode; i++){
        graphAddress p=adjgraphList[i]->head;
        printf("graphList for vertex %d: ", i);
        while(p){
            printf("%d ", p->vertexNum);
            p=p->next;
        }
        printf("\n");
    }
    printf("\n");
}

void linkMapGraph(){
    for (int i=0; i<maxgraphNode; i++){
        adjgraphList[i]=(graphList*)malloc(sizeof(graphList));
        adjgraphList[i]->head=NULL;
    }
    addgraphNode(0,1);
    addgraphNode(0,2);
    addgraphNode(1,0);
    addgraphNode(1,3);
    addgraphNode(2,3);
    addgraphNode(2,0);
    addgraphNode(3,1);
    addgraphNode(3,2);
// printgraphList();
// getc();
}

boolean isGraphConnected(int src, int dest){
    for(int i=0; i<maxgraphNode; i++){
        graphAddress p=adjgraphList[i]->head;
        // while(p){
            if (p->vertexNum==src){
            	p=p->next;
            	while(p){
            		if (p->vertexNum==dest)
                        return true;
                    p = p->next;
				}
            }
        //     p=p->next;
        // }
    }
    return false;
}
