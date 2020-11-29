// Nama : Muhammad Afif Akromi
// NIM : 13519110

#include <stdio.h>
#include <stdlib.h>
#include "prioqueuechar.h"


boolean QueueIsEmpty (PrioQueueChar Q){
    return ((Head(Q) == QueueNil) && (Tail(Q) == QueueNil));
}

boolean QueIsFull (PrioQueueChar Q){
    return (NBElmtQueue(Q) == QueueMaxEl(Q));
}

int NBElmtQueue (PrioQueueChar Q){
    // if (Head(Q) == QueueNil && Tail(Q) == QueueNil) { // ?????
    // // if (!(Head(Q) || Tail(Q))) {
    //     return 0;
    // }
    // else if (Head(Q) <= Tail(Q)){
    //     return (Tail(Q)-Head(Q) + 1);
    // }
    // else{
    //     return (QueueMaxEl(Q)-Head(Q) + Tail(Q) + 1);
    // }
    if (QueueIsEmpty(Q)) {
        return 0;
    } else {
        if (Tail(Q) >= Head(Q)) {
            return (Tail(Q)-Head(Q)+1);
        } else {
            return (QueueMaxEl(Q)+Tail(Q)-Head(Q)+1);
        }
    }

}

void MakeEmptyQueue (PrioQueueChar * Q, int Max){
    (*Q).T = (queueElmtType *) malloc ((Max) * sizeof(queueElmtType));
    if ((*Q).T != NULL){
        QueueMaxEl(*Q) = Max;
        Head(*Q) = QueueNil;
        Tail(*Q) = QueueNil;
    } else {
        QueueMaxEl(*Q) = 0;
    }

}

void QueueDealokasi(PrioQueueChar * Q){
    free((*Q).T);
    QueueMaxEl(*Q) = 0;
}

void Enqueue (PrioQueueChar * Q, queueElmtType X){
    if(Head(*Q) == QueueNil) {
        Head(*Q) = 0;
        Tail(*Q) = 0;
        QueueInfoHead(*Q) = X;
    }
    else {
        Tail(*Q) = (Tail(*Q) + 1) % QueueMaxEl(*Q);
        QueueInfoTail(*Q) = X;
        int a1 = Tail(*Q);
        int a2 = (a1 + QueueMaxEl(*Q) - 1)% QueueMaxEl(*Q);
        queueElmtType temp;
        while (a1 != Head(*Q) && Prio(QueueElmt(*Q, a1)) < Prio(QueueElmt(*Q, a2))){
            temp = QueueElmt(*Q, a1);
            QueueElmt(*Q, a1) = QueueElmt(*Q, a2);
            QueueElmt(*Q, a2) = temp;
            a1 = a2;
            a2 = (a1 + QueueMaxEl(*Q) - 1)% QueueMaxEl(*Q);
        }
    }
}

void Dequeue (PrioQueueChar * Q, queueElmtType * X){
    *X= QueueInfoHead(*Q);
    if (NBElmtQueue(*Q) == 1) {
        Head(*Q) = QueueNil;
        Tail(*Q) = QueueNil;
    }
    else {
        Head(*Q)++;
        Head(*Q) %= QueueMaxEl(*Q);
    }
}

void PrintPrioQueueChar (PrioQueueChar Q){
    int temp;
    for (int i = 0; i < NBElmtQueue(Q);i++){
        temp = (Head(Q)+i+QueueMaxEl(Q)) % QueueMaxEl(Q);
        printf("%d \n", QueueElmt(Q,temp).prio);
    }

    printf("#\n");
}
