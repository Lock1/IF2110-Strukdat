// Driver point
// 13519110 / Mohammad Afif Akromi
#include <stdio.h>
#include "../boolean.h"
#include "../point.h"

int main() {

  POINT P1;
  POINT P2;

  puts("Masukkan point P1");
  BacaPOINT(&P1);
  puts("Masukkan point P2");
  BacaPOINT(&P2);

  if (EQ(P1, P2))
    puts("P1 Sama dengan P2");
  if (IsOrigin(P1))
    puts("Origin P1");
  if (IsOrigin(P2))
    puts("Origin P2");

  printf("Kuadran P1 : %d\n",Kuadran(P1));
  printf("Kuadran P2 : %d\n",Kuadran(P2));

  Mirror(&P1, true);
  TulisPOINT(P1);
  return 0;
}
