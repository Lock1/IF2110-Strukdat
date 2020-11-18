// Graph
// 13519146 / Fadel Ananda Dotty
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


void ReadGraph(address ad[], int nbNode)
{
    address new_node;
    int k, val;
    for(int i=0; i<nbNode; i++){
        address last = NULL;
        printf("Masukkan jumlah tetangga node %d: ", i+1);
        scanf("%d", &k);
        for(int j=0; j<k; j++){
            printf("Masukkan nilai tetangga node %d: ", i+1);
            scanf("%d", &val);
            new_node = (address) malloc(sizeof(address));
            new_node->info=val;
            new_node->next=NULL;
            if(ad[i]==NULL)
                ad[i]=new_node;
            else
                last->next=new_node;
            last=new_node;

        }
    }
}


void PrintGraph(address ad[], int nbNode){
    address Ptr=NULL;
    for (int i=0; i<nbNode; i++){
        Ptr=ad[i];
        printf("\n The neighbours of %d are: ", i+1);
        while(Ptr!=NULL){
            printf("%d\t", Ptr->info);
            Ptr=Ptr->next;
        }
    }
}
