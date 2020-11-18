// ADT Stack
// 13519206 / Muhammad Fawwaz Naabigh
#include "stack.h"



/* Membuat sebuah stack S yang kosong berkapasitas MaxEl */
void CreateEmpty (Stack *S){
    Top(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */

/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsEmpty (Stack S){
    return Top(S) == Nil;
}

/* Mengirim true jika tabel penampung nilai elemen stack penuh */
boolean IsFull (Stack S){
    return Top(S) == MaxEl-1;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */

/* Menambahkan X sebagai elemen Stack S. */
void Push (Stack * S, infotype X){
    Top(*S)++;
    InfoTop(*S) = X;
}

/* Menghapus X dari Stack S. */
void Pop (Stack * S, infotype* X){
    *X = InfoTop(*S);
    Top(*S)--;
}
