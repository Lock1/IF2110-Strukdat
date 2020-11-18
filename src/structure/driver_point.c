#include <stdio.h>
#include "boolean.h"
#include "point.h"
#include <math.h>

int main() {

  POINT P1;
  POINT P2;

  BacaPOINT(&P1);
  BacaPOINT(&P2);

  boolean isSama = EQ(P1, P2);
  boolean isOrigin = IsOrigin(P1);
  boolean isOrigin = IsOrigin(P2);

  int kuadranP1 = Kuadran(P1);
  int kuadranP2 = Kuadran(P2);

  int jarakP1 = Jarak0(P1);
  int jarakP2 = Jarak0(P2);
  int panjangP1P2 = Panjang(P1, P2);
  
  Mirror(&P1, true);
  return 0;
}