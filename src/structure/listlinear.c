#include "listlinear.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

//Nama  : Fadel Ananda D
//NIM   : 13519146

/****************** TEST LIST KOSONG ******************/
boolean LinIsEmpty (List L){
    return First(L)==Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void LinCreateEmpty (List *L){
    First(*L)=Nil;
}

/****************** Manajemen Memori ******************/
address LinAlokasi (infotype X){
    address P=(address) malloc(1*sizeof(ElmtList));
    if (P!=Nil){
        Info(P)=X;
        Next(P)=Nil;
    }
    return P;
}

void DeLinAlokasi (address *P){
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address LinSearch (List L, infotype X){
  address P;
  boolean xFound = false;

  if (!LinIsEmpty(L)) {
    P = First(L);
    while (!xFound && P != Nil) {
      if (X == Info(P)) {
        xFound = true;
      } else {
        P = Next(P);
      }
    }

    if (xFound) {
      return P;
    } else {
      return Nil;
    }

  } else {
    return Nil;
  }
}

/****************** PRIMITIF BERDASARKAN NilAI ******************/
void InsVLast (List *L, infotype X){
    address P=LinAlokasi(X);
    if (P!=Nil){
        InsertLast(L, P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVLast (List *L, infotype *X){
    address P=First(*L);
    address Prec=Nil;

    while (Next(P)!=Nil){
        Prec=P;
        P=Next(P);
    }

    if (Prec==Nil)
        First(*L)=Nil;
    else{
        Next(Prec)=Nil;
    }
    *X=Info(P);
    DeLinAlokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertAfter (address P, address Prec){
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void InsertLast (List *L, address P){
  address Last;

  if (LinIsEmpty(*L)) {
    Next(P)=First(*L);
    First(*L)=P;
  } else {
    Last = First(*L);
    while (Next(Last) != Nil) {
      Last = Next(Last);
    }
    InsertAfter(P, Last);
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelLast (List *L, address *P){
    address Last=First(*L);
    address PrecLast=Nil;

    while (Next(Last)!=Nil){
        PrecLast=Last;
        Last=Next(Last);
    }

    *P=Last;
    if (PrecLast==Nil)
        First(*L)=Nil;
    else{
        Next(PrecLast)=Nil;
    }
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L){
  address P;
  boolean isFirst = true;

  printf("[");
  if (!LinIsEmpty(L)) {
    P = First(L);
    while (P != Nil) {
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

int LinNBElmt (List L){
    address P;
    int count=0;

    if(!LinIsEmpty(L)){
        P=First(L);
        while (P!=Nil){
            count+=1;
            P=Next(P);
        }
    }

    return count;
}
