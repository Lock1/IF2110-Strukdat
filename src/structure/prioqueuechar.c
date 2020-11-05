// Nama : Muhammad Afif Akromi
// NIM : 13519110

#include <stdio.h>
#include "stdlib.h"
#include "prioqueuechar.h"

boolean IsEmpty (PrioQueueChar Q){
    return (Head(Q) == Nil && Tail(Q) == Nil);
}

boolean IsFull (PrioQueueChar Q){
    return (NBElmt(Q) == MaxEl(Q));
}

int NBElmt (PrioQueueChar Q){
    if (IsEmpty(Q)){
        return 0;
    }
    else if (Head(Q) <= Tail(Q)){
        return (Tail(Q)-Head(Q) + 1);
    }
    else{
        return (MaxEl(Q)-Head(Q) + Tail(Q) + 1);
    }
}

void MakeEmpty (PrioQueueChar * Q, int Max){
    (*Q).T = (infotype *) malloc ((Max) * sizeof(infotype));
    if ((*Q).T != NULL){    
        MaxEl(*Q) = Max;
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    } else {
        MaxEl(*Q) = 0;
    }
    
}

void DeAlokasi(PrioQueueChar * Q){
    free((*Q).T);
    MaxEl(*Q) = 0;
}

void Enqueue (PrioQueueChar * Q, infotype X){
    if(Head(*Q) == Nil)   Head(*Q) = 0;
    Tail(*Q) = (Tail(*Q) + 1) % MaxEl(*Q);
    InfoTail(*Q) = X;
    int a1 = Tail(*Q);
    int a2 = (a1 + MaxEl(*Q) - 1)% MaxEl(*Q);
    infotype temp;
    while (a1 != Head(*Q) && Prio(Elmt(*Q, a1)) < Prio(Elmt(*Q, a2))){
        temp = Elmt(*Q, a1);
        Elmt(*Q, a1) = Elmt(*Q, a2);
        Elmt(*Q, a2) = temp;
        a1 = a2;
        a2 = (a1 + MaxEl(*Q) - 1)% MaxEl(*Q);
    }
}

void Dequeue (PrioQueueChar * Q, infotype * X){
    *X= InfoHead(*Q);
    if (NBElmt(*Q) == 1) {
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else {
        Head(*Q)++;
        Head(*Q) %= MaxEl(*Q);
    }
}

void PrintPrioQueueChar (PrioQueueChar Q){
    int temp;
    for (int i = 0; i < NBElmt(Q);i++){
        temp = (Head(Q)+i+MaxEl(Q)) % MaxEl(Q);
        printf("%d %c\n", Elmt(Q,temp).prio,Elmt(Q,temp).info);
    }

    printf("#\n");
}

