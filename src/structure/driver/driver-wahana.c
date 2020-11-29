// Driver wahana
// 13519110 / Mohammad Afif Akromi
#include <stdio.h>
#include "stdlib.h"
#include "../wahana.h"
#include "../wahana.c"
#include "../listlinear.h"
#include "../listlinear.c"

int main() {
  
  Wahana* W = createWahanaByID(W, 1);
  Harga(*W) = 1000;
  WahanaDurasi(*W) = 3600;
  Kapasitas(*W) = 10;
  Frekuensi(*W) = 100;
  FrekuensiHari(*W) = 20;
  Penghasilan(*W) = 5000;
  PenghasilanHari(*W) = 2000;
  
  printf("Harga: %d\n", Harga(*W));
  printf("WahanaDurasi: %d\n", WahanaDurasi(*W));
  printf("Kapasitas: %d\n", Kapasitas(*W));
  printf("Frekuensi: %d\n", Frekuensi(*W));
  printf("FrekuensiHari: %d\n", FrekuensiHari(*W));
  printf("Penghasilan: %d\n", Penghasilan(*W));
  printf("PenghasilanHari: %d\n\n", PenghasilanHari(*W));

  printf("SearchWahanaById: %d\n", searchWahanaByID(W, 1));
  printf("getHargaWahanaByID: %d\n", getHargaWahanaByID(W, 1));
  printf("getWahanaDurasiByID: %d\n", getWahanaDurasiByID(W, 1));
  printf("getKapasitasByID: %d\n", getKapasitasByID(W, 1));
  printf("getFrekuensiByID: %d\n", getFrekuensiByID(W, 1));
  printf("getStatusWahanaByID: %d\n", getStatusWahanaByID(W, 1));
  printf("getIndexByID: %d\n", getIndexByID(W, 1));
  printf("getCharByID: %d\n", getCharByID(W, 1));

  return 0;
}