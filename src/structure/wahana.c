#include <stdio.h>
#include "boolean.h"
#include "wahana.h"
#include <math.h>

Wahana MakeWahana(int id, int harga, int durasi, int kapasitas, char nama[999], char deskripsi, char gambar) {
  Wahana W;
  ID(W) = id;
  Durasi(W) = durasi;
  Kapasitas(W) = kapasitas;
  Nama(W) = nama;
  Deskripsi(W) = deskripsi;
  Gambar(W) = gambar;

  return W;
}

int getIDWahana(Wahana W) {
  return ID(W);
}

int getHargaWahana(Wahana W) {
  return Harga(W);
}

int getDurasiWahana(Wahana W) {
  return Durasi(W);
}

int getKapasitasWahana(Wahana W) {
  return Kapasitas(W);
}

int getKapasitasWahana(Wahana W) {
  return Kapasitas(W);
}

int getFrekuensiWahana(Wahana W) {
  return Frekuensi(W);
}

int getPenghasilanWahana(Wahana W) {
  return Penghasilan(W);
}

int getPenghasilanHariWahana(Wahana W) {
  return PenghasilanHari(W);
}

int getFrekuensiHariWahana(Wahana W) {
  return FrekuensiHari(W);
}

int getStatusWahana(Wahana W) {
  return StatusWahana(W);
}

char getNamaWahana(Wahana W) {
  return Nama(W);
}

char getDeskripsi(Wahana W) {
  return Deskripsi(W);
}

char getGambar(Wahana W) {
  return Gambar(W);
}

void setStatusWahana(Wahana* W, int newStatus) {
  StatusWahana(*W) = newStatus;
}