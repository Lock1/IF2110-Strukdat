// Driver prioqueuechar
// 13519110 / Mohammad Afif Akromi
#include <stdio.h>
#include "stdlib.h"
#include "../prioqueuechar.h"
#include "../prioqueuechar.c"

int main() {
  PrioQueueChar Q;
  queueElmtType X, Y;

  MakeEmptyQueue(&Q, 10);
  Enqueue(&Q, X);
  Enqueue(&Q, Y);

  Head(Q) = 4;
  Tail(Q) = 5;
  X.isServed[0] = false;
  X.prio = 100;
  X.info[0] = 10;
  X.happiness = 1;

  Y.isServed[0] = true;
  Y.prio = 50;
  Y.info[0] = 9;
  Y.happiness = 1;

  printf("Head: %d\n", Head(Q));
  printf("Head: %d\n", Tail(Q));
  printf("QueueMaxEl: %d\n", QueueMaxEl(Q));
  printf("NBElmtQueue: %d\n", NBElmtQueue(Q));
  printf("QueIsFull: %d\n", QueIsFull(Q));
  printf("QueueIsEmpty: %d\n", QueueIsEmpty(Q));
  printf("PrioX: %d\n", X.prio);
  printf("InfoX: %d\n", X.info[0]);
  printf("HappinessX: %d\n", X.happiness);
  printf("isServedX: %d\n\n", X.isServed[0]);
  printf("PrioY: %d\n", Y.prio);
  printf("InfoY: %d\n", Y.info[0]);
  printf("HappinessY: %d\n", Y.happiness);
  printf("isServedY: %d\n\n", Y.isServed[0]);
  Dequeue(&Q, &Y);
  printf("NBElmtQueue: %d\n", NBElmtQueue(Q));
  PrintPrioQueueChar(Q);

  return 0;
}
