#ifndef _WAHANA_H_
#define _WAHANA_H_

#include "boolean.h"

typedef struct {
	int ID, harga, durasi, kapasitas, frekuensiTotal, penghasilanTotal, penghasilanHari, frekuensiHari, statusWahana;
	char nama[999];
	char deskripsi[999];
  char gambar[999];
} Wahana;

#define ID(W) (W).ID
#define Harga(W) (W).harga
#define Durasi(W) (W).durasi
#define Kapasitas(W) (W).kapasitas
#define Frekuensi(W) (W).frekuensiTotal
#define Penghasilan(W) (W).penghasilanTotal
#define PenghasilanHari(W) (W).penghasilanHari
#define FrekuensiHari(W) (W).frekuensiHari
#define StatusWahana(W) (W).statusWahana
#define Nama(W) (W).nama[999]
#define Deskripsi(W) (W).deskripsi[999]
#define Gambar(W) (W).gambar[999]

Wahana MakeWahana(int ID, int harga, int durasi, int kapasitas, char nama, char deskripsi, char gambar);

int getIDWahana(Wahana W);

int getHargaWahana(Wahana W);

int getDurasiWahana(Wahana W);

int getKapasitasWahana(Wahana W);

int getKapasitasWahana(Wahana W);

int getFrekuensiWahana(Wahana W);

int getPenghasilanWahana(Wahana W);

int getPenghasilanHariWahana(Wahana W);

int getFrekuensiHariWahana(Wahana W);

int getStatusWahana(Wahana W);

char getNamaWahana(Wahana W);

char getDeskripsi(Wahana W);

char getGambar(Wahana W);

void setStatusWahana(Wahana* W, int newStatus);

#endif