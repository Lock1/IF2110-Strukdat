#ifndef listlinear_H
#define listlinear_H

#include "boolean.h"

#define Nil NULL

typedef int infotype;
typedef struct tElmtlist *address;
typedef struct tElmtlist {
	infotype info;
	address next;
} ElmtList;
typedef struct {
	address First;
} List;

#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)


/****************** TEST KETIKA BELUM DI UPGRADE ******************/
boolean LinIsEmpty (List L);


/****************** PEMBUATAN LIST KOSONG ******************/
void LinCreateEmpty (List *L);


/****************** Manajemen Memori ******************/
address LinAlokasi (infotype X);

void LinDealokasi (address *P);


/****************** Pencarian Upgrade ******************/
address LinSearch (List L, infotype X);
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
void InsVLast (List *L, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan LinAlokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* berNilai X jika LinAlokasi berhasil. Jika LinAlokasi gagal: I.S.= F.S. */

void DelVLast (List *L, infotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: Nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-LinDealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertAfter (address P, address Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah diLinAlokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

void InsertLast (List *L, address P);
/* I.S. Sembarang, P sudah diLinAlokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

void DelLast (List *L, address *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */


/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L);

int LinNBElmt (List L);
/* Buat mengetahui berapa banyak sudah melakukan upgrade */



#endif
