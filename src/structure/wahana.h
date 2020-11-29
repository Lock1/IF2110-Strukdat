//13519146 - Fadel Ananda Dotty
//13519110 - M. Akromi Afif

#ifndef _WAHANA_H_
#define _WAHANA_H_

#include "boolean.h"
#include "listlinear.h"

typedef struct {
	int ID, harga, durasi, kapasitas, frekuensiTotal, penghasilanTotal, penghasilanHari, frekuensiHari, statusWahana;
	int* materialArray;
	char nama[999];
	char deskripsi[999];
    char gambar;
	ListLin upgrade;
} Wahana;

#define ID(W) (W).ID
#define Harga(W) (W).harga
#define WahanaDurasi(W) (W).durasi
#define Kapasitas(W) (W).kapasitas
#define Frekuensi(W) (W).frekuensiTotal
#define Penghasilan(W) (W).penghasilanTotal
#define PenghasilanHari(W) (W).penghasilanHari
#define FrekuensiHari(W) (W).frekuensiHari
#define StatusWahana(W) (W).statusWahana
#define Nama(W) (W).nama
#define Deskripsi(W) (W).deskripsi
#define Gambar(W) (W).gambar
#define Upgrade(W) (W).upgrade

// Wahana MakeWahana(int ID, int harga, int durasi, int kapasitas, char nama[999], char deskripsi, char gambar);

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

char* getNamaWahana(Wahana W);

char* getDeskripsi(Wahana W);

char getGambar(Wahana W);

void destroyWahana(Wahana* w);

void setStatusWahana(Wahana* W, int newStatus);

Wahana* createWahanaByID(Wahana* w, int ID);

boolean searchWahanaByID(Wahana* w, int ID);

int getHargaWahanaByID(Wahana* w, int ID);

int getIndexByID(Wahana* w, int ID);

char getCharByID(Wahana* w, int ID);
// int CountWahana();
//
// int CountAllWahana();

#endif
