#ifndef _WAHANA_H_
#define _WAHANA_H_

#include "boolean.h"

typedef struct {
	int ID, harga, durasi, kapasitas;
	char nama[999];
	char deskripsi[999];
  char gambar[999];
} Wahana;

Wahana MakeWahana(int ID, int harga, int durasi, int kapasitas, char nama, char deskripsi, char gambar);

#endif