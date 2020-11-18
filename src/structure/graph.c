// ADT Graf
// 13519146 / Fadel Ananda Dotty
#include "graph.h"
#include <stdio.h>
#include <stlib.h>

void addNode(int s, int d){
    address dest, temp, src;
    if(adjlist[s]->head==NULL){
        src=(address)malloc(sizeof(Node));
        src->vertexNum=s;
        src->next=NULL;
        adjlist[s]->head=src;
    }
    dest=(address)malloc(sizeof(Node));
    dest->vertexNum=d;
    dest->next=NULL;
    temp=adjlist[s]->head;
    while (temp->next!=NULL)
        temp=temp->next;
    temp->next=dest;
}

void printList(){
    for(int i=0; i<maxNode; i++){
        address p=adjlist[i]->head;    
        printf("List for vertex %d: ", i);
        while(p){
            printf("%d ", p->vertexNum);
            p=p->next;
        }
        printf("\n");
    }
    printf("\n");
