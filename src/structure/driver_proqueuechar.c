#include <stdio.h>
#include "stdlib.h"
#include "prioqueuechar.h"

int main() {
  PrioQueueChar Q;
  infotype X, Y, Z;
  Prio(X) = 10;
  Info(X) = "A";
  Prio(Y) = 100;
  Info(Y) = "B";
  Prio(Z) = 1000;
  Info(Z) = "C";

  MakeEmpty(&Q, 100);
  Enqueue(&Q, X);
  Enqueue(&Q, Y);
  Enqueue(&Q, Z);

  Dequeue(&Q, &Y);
  DeAlokasi(&Q);
  return 0;
}