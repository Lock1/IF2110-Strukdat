#include <stdio.h>
#include "boolean.h"
#include "wahana.h"

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

Wahana* searchWahana(Wahana* w, int ID){
  Wahana* hasil=(Wahana*)malloc(1*sizeof(Wahana));
  for (int i=0; i<20; i++){
    if (w[i].ID==ID){
      ID(hasil)=ID(w);
      Harga(hasil)=Harga(w);
      Durasi(hasil)=Durasi(w);
      Kapasitas(hasil)=Kapasitas(w);
      Frekuensi(hasil)=Frekuensi(w);
      Penghasilan(hasil)=Penghasilan(w);
      Frekuensi(hasil)=Frekuensi(w);
      StatusWahana(hasil)=StatusWahana(w);
      Nama(hasil)=Nama(w);
      Deskripsi(hasil)=Deskripsi(w);
      Gambar(hasil)=Gambar(w);
    }
  }
  return hasil;
}
