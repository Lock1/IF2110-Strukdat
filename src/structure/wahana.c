#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "wahana.h"

// Wahana MakeWahana(int id, int harga, int WahanaDurasi, int kapasitas, char nama[999], char deskripsi, char gambar) {
//   Wahana W;
//   ID(W) = id;
//   WahanaDurasi(W) = WahanaDurasi;
//   Kapasitas(W) = kapasitas;
//   Nama(W) = nama;
//   Deskripsi(W) = deskripsi;
//   Gambar(W) = gambar;
//
//   return W;
// }

// int getIDWahana(Wahana W) {
//   return ID(W);
// }
//
// int getHargaWahana(Wahana W) {
//   return Harga(W);
// }
//
// int getWahanaDurasiWahana(Wahana W) {
//   return WahanaDurasi(W);
// }
//
// int getKapasitasWahana(Wahana W) {
//   return Kapasitas(W);
// }
//
// int getFrekuensiWahana(Wahana W) {
//   return Frekuensi(W);
// }
//
// int getPenghasilanWahana(Wahana W) {
//   return Penghasilan(W);
// }
//
// int getPenghasilanHariWahana(Wahana W) {
//   return PenghasilanHari(W);
// }
//
// int getFrekuensiHariWahana(Wahana W) {
//   return FrekuensiHari(W);
// }
//
// int getStatusWahana(Wahana W) {
//   return StatusWahana(W);
// }
//
// char* getNamaWahana(Wahana W) {
//   return Nama(W);
// }
//
// char* getDeskripsi(Wahana W) {
//   return Deskripsi(W);
// }
//
// char getGambar(Wahana W) {
//   return Gambar(W);
// }

void setStatusWahana(Wahana* W, int newStatus) {
  StatusWahana(*W) = newStatus;
}

Wahana* createWahanaByID(Wahana* w, int ID){
  Wahana* hasil=(Wahana*)malloc(1*sizeof(Wahana));
  for (int i=0; i<20; i++){
    if (w[i].ID==ID){
      ID(*hasil)=ID(w[i]);
      Harga(*hasil)=Harga(w[i]);
      WahanaDurasi(*hasil)=WahanaDurasi(w[i]);
      Kapasitas(*hasil)=Kapasitas(w[i]);
      Frekuensi(*hasil)=Frekuensi(w[i]);
      Penghasilan(*hasil)=Penghasilan(w[i]);
      Frekuensi(*hasil)=Frekuensi(w[i]);
      StatusWahana(*hasil)=StatusWahana(w[i]);
      for (int j = 0 ; j < 999 ; j++) {
          Nama(*hasil)[j] = Nama(w[i])[j];
          Deskripsi(*hasil)[j] = Deskripsi(w[i])[j];
      }
      Gambar(*hasil)=Gambar(w[i]);
    }
  }
  return hasil;
}

boolean searchByID(Wahana* w, int ID){
  for (int i=0; i<20; i++){
    if (w[i].ID==ID){
      return true;
    }
  }
  return false;
}
