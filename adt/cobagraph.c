#include "boolean.h"

typedef struct tnode *address;
typedef struct tnode{
    int info;
    address up;
    address down;
    address left;
    address right;
} node;
typedef struct {
    address Center;
}Graph;


#define Center(G) ((G).Center)
#define Up(P) ((G).up)
#define Down(P) ((G).down)
#define Left(P) ((G).left)
#define Right(P) ((G).right)

boolean isNotConnected (Graph G){
    return ((Up(G)==NULL) && (Down(G)==NULL) && (Left(G)==NULL) && (Right(G)==NULL));
}

void CreateGraph (Graph *L){
    First(*G)=NULL;
}

address Alokasi (int X){
    address P=(address) malloc(1*sizeof(node));

    if(P!=NULL){
        Info(P)=X;
        Next(P)=NULL;
        Prev(P)=NULL;
        return P;
    }
    else{
        return NULL;
    }
}

void Dealokasi (address P){
    free(P);
}

void InsertUp(List *L, address P, address Prec){
    Up(P) = Up(Prec);
    Up(Prec) = P;
}

void InsertDown(List *L, address P, address Prec){
    Down(P) = Down(Prec);
    Down(Prec) = P;
}