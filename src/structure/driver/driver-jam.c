// Nama : Dwianditya Hanif
// NIM : 13519046
// Tanggal : 30 September 2020
// Topik : Mesin Kata
// Deskripsi : Implementasi driver-jam.c
/* File : mjam.c */
/* Program MainJam */
/* Driver ADT Jam */
#include <stdio.h>
#include "../jam.h"

int main()
{   /* KAMUS */
    JAM J1, J2;
    /* ALGORITMA */
    puts("Masukkan jam dalam format JJ MM");
    BacaJAM(&J1);
    printf("Jam sekarang: ");
    TulisJAM(J1); printf("\n");
    printf("Konversi menjadi menit: %ld\n",JAMToMenit(J1));
    J2 = MenitToJAM(5000);
    printf("5000 menit sama dengan jam : ");
    TulisJAM(J2); printf("\n");



    printf("10 menit setelah J1 adalah ");
    TulisJAM(NextNMenit(J1, 10));
    printf("\n");
    printf("Durasi dari J1 dan J2 adalah %ld menit", Durasi(J1, J2));

    return 0;
}
