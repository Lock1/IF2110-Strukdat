#ifndef listlinear_H
#define listlinear_H

#include "boolean.h"

#define listLinNil NULL

typedef int listLinInfotype;
typedef struct tlistLinElmtList *listLinAddress;
typedef struct tlistLinElmtList {
	listLinInfotype info;
	listLinAddress next;
} listLinElmtList;
typedef struct {
	listLinAddress First;
} ListLin;

#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)


/****************** TEST KETIKA BELUM DI UPGRADE ******************/
boolean LinIsEmpty (ListLin L);


/****************** PEMBUATAN ListLin KOSONG ******************/
void LinCreateEmpty (ListLin *L);


/****************** Manajemen Memori ******************/
listLinAddress LinAlokasi (listLinInfotype X);

void LinDealokasi (listLinAddress *P);


/****************** Pencarian Upgrade ******************/
listLinAddress LinSearch (ListLin L, listLinInfotype X);
/* Mencari apakah ada elemen ListLin dengan Info(P)= X */
/* Jika ada, mengirimkan listLinAddress elemen tersebut. */
/* Jika tidak ada, mengirimkan listLinNil */

/****************** PRIMITIF BERDASARKAN listLinNilAI ******************/
void InsVLast (ListLin *L, listLinInfotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan LinAlokasi sebuah elemen dan */
/* menambahkan elemen ListLin di akhir: elemen terakhir yang baru */
/* berlistLinNilai X jika LinAlokasi berhasil. Jika LinAlokasi gagal: I.S.= F.S. */

void DelVLast (ListLin *L, listLinInfotype *X);
/* I.S. ListLin tidak kosong */
/* F.S. Elemen terakhir ListLin dihapus: listLinNilai info disimpan pada X */
/*      dan alamat elemen terakhir di-LinDealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertAfter (listLinAddress P, listLinAddress Prec);
/* I.S. Prec pastilah elemen ListLin dan bukan elemen terakhir, */
/*      P sudah diLinAlokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

void InsertLast (ListLin *L, listLinAddress P);
/* I.S. Sembarang, P sudah diLinAlokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

void DelLast (ListLin *L, listLinAddress *P);
/* I.S. ListLin tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListLin sebelum penghapusan  */
/*      Elemen ListLin berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */


/****************** PROSES SEMUA ELEMEN ListLin ******************/
void PrintInfo (ListLin L);

int LinNBElmt (ListLin L);
/* Buat mengetahui berapa banyak sudah melakukan upgrade */



#endif
