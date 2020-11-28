#include "listlinear.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

//Nama  : Fadel Ananda D
//NIM   : 13519146

/****************** TEST ListLin KOSONG ******************/
boolean LinIsEmpty (ListLin L){
    return First(L)==listLinNil;
}

/****************** PEMBUATAN ListLin KOSONG ******************/
void LinCreateEmpty (ListLin *L){
    First(*L)=listLinNil;
}

/****************** Manajemen Memori ******************/
listLinAddress LinAlokasi (listLinInfotype X){
    listLinAddress P=(listLinAddress) malloc(1*sizeof(listLinElmtList));
    if (P!=listLinNil){
        Info(P)=X;
        Next(P)=listLinNil;
    }
    return P;
}

void DeLinAlokasi (listLinAddress *P){
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN ListLin ******************/
listLinAddress LinSearch (ListLin L, listLinInfotype X){
  listLinAddress P;
  boolean xFound = false;

  if (!LinIsEmpty(L)) {
    P = First(L);
    while (!xFound && P != listLinNil) {
      if (X == Info(P)) {
        xFound = true;
      } else {
        P = Next(P);
      }
    }

    if (xFound) {
      return P;
    } else {
      return listLinNil;
    }

  } else {
    return listLinNil;
  }
}

/****************** PRIMITIF BERDASARKAN listLinNilAI ******************/
void InsVLast (ListLin *L, listLinInfotype X){
    listLinAddress P=LinAlokasi(X);
    if (P!=listLinNil){
        InsertLast(L, P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVLast (ListLin *L, listLinInfotype *X){
    listLinAddress P=First(*L);
    listLinAddress Prec=listLinNil;

    while (Next(P)!=listLinNil){
        Prec=P;
        P=Next(P);
    }

    if (Prec==listLinNil)
        First(*L)=listLinNil;
    else{
        Next(Prec)=listLinNil;
    }
    *X=Info(P);
    DeLinAlokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertAfter (listLinAddress P, listLinAddress Prec){
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void InsertLast (ListLin *L, listLinAddress P){
  listLinAddress Last;

  if (LinIsEmpty(*L)) {
    Next(P)=First(*L);
    First(*L)=P;
  } else {
    Last = First(*L);
    while (Next(Last) != listLinNil) {
      Last = Next(Last);
    }
    InsertAfter(P, Last);
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelLast (ListLin *L, listLinAddress *P){
    listLinAddress Last=First(*L);
    listLinAddress PrecLast=listLinNil;

    while (Next(Last)!=listLinNil){
        PrecLast=Last;
        Last=Next(Last);
    }

    *P=Last;
    if (PrecLast==listLinNil)
        First(*L)=listLinNil;
    else{
        Next(PrecLast)=listLinNil;
    }
}


/****************** PROSES SEMUA ELEMEN ListLin ******************/
void PrintInfo (ListLin L){
  listLinAddress P;
  boolean isFirst = true;

  printf("[");
  if (!LinIsEmpty(L)) {
    P = First(L);
    while (P != listLinNil) {
      if (!isFirst) {
        printf(",");
      }
      printf("%d", Info(P));
      isFirst = false;

      P = Next(P);
    }
  }
  printf("]");
}

int LinNBElmt (ListLin L){
    listLinAddress P;
    int count=0;

    if(!LinIsEmpty(L)){
        P=First(L);
        while (P!=listLinNil){
            count+=1;
            P=Next(P);
        }
    }

    return count;
}
