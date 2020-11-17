// Driver graph
// 13519146 / Fadel Ananda Dotty
#include <stdio.h>
#include <stdlib.h>
#include "../graph.h"

int main(){
    int nodes;
    printf("Masukkan jumlah node: ");
    scanf("%d", &nodes);

    address adj[nodes];
    for(int i=0; i<nodes; i++)
        adj[i]=NULL;
    ReadGraph(adj, nodes);
    PrintGraph(adj, nodes);
    return 0;
}
