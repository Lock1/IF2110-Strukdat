/* NAMA : MOHAMMAD AFIF AKROMI */
/* NIM  : 13519110 */
/* KELAS : K02 */
/* PRA PRAKTIKUM 7 Oktober 2020 */

#include "queue.h"
#include <stdio.h> 
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q) {
    return ((Head(Q) == Nil) && (Tail(Q) == Nil));
}
/* Mengirim true jika Q kosong: lihat definisi di atas */

boolean IsFull (Queue Q) {
    boolean isFull = false;

    if (Head(Q) < Tail(Q)) {
        isFull = (Head(Q) == 0) && (Tail(Q) == MaxEl(Q)-1);
    } else if (Head(Q) > Tail(Q)) {
        isFull = (Head(Q) == (Tail(Q) + 1));
    }

    return isFull;
}
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */

int NBElmt (Queue Q) {
    int total = 0;

    if (!IsEmpty(Q)) {
        if (Head(Q) < Tail(Q)) {
            total = (Tail(Q) - Head(Q) + 1);
        } else if (Head(Q) > Tail(Q)) {
            total = (MaxEl(Q) - Head(Q)) + Tail(Q) + 1;
        }
    }

    return total;
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void MakeEmpty (Queue* Q, int Max) {
    (*Q).T = (infotype *) malloc(Max*sizeof(infotype));

    if ((*Q).T != NULL) {
        MaxEl(*Q) = Max;
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    } else {
        MaxEl(*Q) = 0;
    }
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(Queue * Q) {
    MaxEl(*Q) = 0;
    free((*Q).T);
}
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Enqueue (Queue * Q, infotype X) {
    if (IsEmpty(*Q)) {
        Head(*Q) = 0;
        Tail(*Q) = 0;
        InfoHead(*Q) = X;
    } else {
        if (Tail(*Q) == MaxEl(*Q)-1) {
            Tail(*Q) = 0;
            InfoTail(*Q) = X;
        } else {
            Tail(*Q)++;
            InfoTail(*Q) = X;
        }
    }
}
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */

void Dequeue (Queue* Q, infotype* X) {
    *X = InfoHead(*Q);
    if (Head(*Q) == Tail(*Q)) {
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    } else {
        if (Head(*Q) == MaxEl(*Q)-1) {
            Head(*Q) = 0;
        } else {
            Head(*Q)++;
        }
    }
}
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

void RoundRobin(Queue* Q, infotype T) {
    infotype infoHead = InfoHead(*Q);
    if (infoHead < T) {
        Dequeue(Q, &infoHead);
    } else {
        int newTime = InfoHead(*Q) - T;
        Dequeue(Q, &infoHead);
        Enqueue(Q, newTime);
    }
}

void PrintQueue(Queue* Q) {
    if (Head(*Q) < Tail(*Q)) {
        for (int i=Head(*Q); i<=Tail(*Q); i++) {
            printf("%d ", Q->T[i]);
        }
    } else {
        int i = Head(*Q);
        int max = MaxEl(*Q);

        while (i <= max) {
            if (i == MaxEl(*Q)) {
                i = 0;
                max = Tail(*Q);
            }

            printf("i = %d\n ", i);
            printf("%d \n", Q->T[i]);
            i++;
        }
    }
} 