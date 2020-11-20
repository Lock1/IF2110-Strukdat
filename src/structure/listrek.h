/* File: listrek.h */
/* ADT list linier dengan representasi pointer */
/* Implementasi list linier secara rekursif */

#ifndef _LISTREK_H_
#define _LISTREK_H_

#include "boolean.h"

#define ListNil NULL

/* Definisi Type */
typedef int listrekInfotype;
typedef struct tElmtlist *listRekAddress;
typedef struct tElmtlist {
	listrekInfotype info;
	listRekAddress next;
} ElmtList;

/* Definisi list : */
/* List kosong : L = ListNil */
typedef listRekAddress List;

/* Deklarasi  nama untuk variabel kerja */
/*  	L : List */
/*  	P : listRekAddress 	*/
/* Maka penulisan First(L) menjadi L */
/*                P.info menjadi Info(P); P.next menjadi Next(P) */

/* Selektor */
#define Info(P) (P)->info
#define Next(P) (P)->next

/* *** Manajemen Memori *** */
listRekAddress Alokasi (listrekInfotype X);
/* Mengirimkan listRekAddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka listRekAddress tidak ListNil, dan misalnya menghasilkan P,
  maka Info(P) = X, Next(P) = ListNil */
/* Jika alokasi gagal, mengirimkan ListNil */
void Dealokasi (listRekAddress P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian listRekAddress P */

/* *** Primitif-primitif yang harus direalisasikan *** */

/* Pemeriksaan Kondisi List */
int RekIsEmpty(List L);
/* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */
int IsOneElmt(List L);
/* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */

/* *** Selektor *** */
listrekInfotype FirstElmt (List L);
/* Mengirimkan elemen pertama sebuah list L yang tidak kosong */
List Tail(List L);
/* Mengirimkan list L tanpa elemen pertamanya, mungkin menjadi list kosong */

/* *** Konstruktor *** */
List Konso(listrekInfotype e, List L);
/* Mengirimkan list L dengan tambahan e sebagai elemen pertamanya.
e dialokasi terlebih dahulu. Jika alokasi gagal, mengirimkan L. */
List KonsB(List L, listrekInfotype e);
/* Mengirimkan list L dengan tambahan e sebagai elemen terakhirnya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan L */

/* *** Operasi Lain *** */
List Copy (List L);
/* Mengirimkan salinan list L (menjadi list baru) */
/* Jika ada alokasi gagal, mengirimkan L */
void MCopy (List Lin, List *Lout);
/* I.S. Lin terdefinisi */
/* F.S. Lout berisi salinan dari Lin */
/* Proses : menyalin Lin ke Lout */
List Concat (List L1, List L2);
/* Mengirimkan salinan hasil konkatenasi list L1 dan L2 (menjadi list baru) */
/* Jika ada alokasi gagal, menghasilkan ListNil */
void MConcat (List L1, List L2, List *LHsl);
/* I.S. L1, L2 terdefinisi */
/* F.S. LHsl adalah hasil melakukan konkatenasi L1 dan L2 dengan cara "disalin" */
/* Proses : Menghasilkan salinan hasil konkatenasi list L1 dan L2 */
void PrintList (List L);
/* I.S. L terdefinisi. */
/* F.S. Setiap elemen list dicetak. */
int NbElmtList (List L);
/* Mengirimkan banyaknya elemen list L, Nol jika L kosong */
boolean Search (List L, listrekInfotype X);
/* Mengirim true jika X adalah anggota list, false jika tidak */

#endif
