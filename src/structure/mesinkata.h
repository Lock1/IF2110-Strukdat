// Nama : Dwianditya Hanif
// NIM : 13519046
// Tanggal : 30 September 2020
// Topik : Mesin Kata
// Deskripsi : Implementasi mesinkata.h

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../config.h"
#include "boolean.h"
#include "mesinkar.h"

#define BLANK ' '

typedef struct {
	char TabKata[STRING_LENGTH]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

#define CurrentInput CKata.TabKata
#define LengthInput CKata.Length

void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void wordInput();
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

#endif
