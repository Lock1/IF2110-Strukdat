#include "listlinier.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

//Nama  : Fadel Ananda D
//NIM   : 13519146

/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L){
    return First(L)==Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L){
    First(*L)=Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X){
    address P=(address) malloc(1*sizeof(ElmtList));
    if (P!=Nil){
        Info(P)=X;
        Next(P)=Nil;
    }
    return P;
}

void Dealokasi (address *P){
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X){
  address P;
  boolean xFound = false;

  if (!IsEmpty(L)) {
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
void InsVFirst (List *L, infotype X){
    address P=Alokasi(X);
    if (P!=Nil){
        InsertFirst(L, P);
    }
}

void InsVLast (List *L, infotype X){
    address P=Alokasi(X);
    if (P!=Nil){
        InsertLast(L, P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X){
    address P=First(*L);
    First(*L)=Next(P);
    Next(P)=Nil;
    *X=Info(P);
    Dealokasi(&P);
}

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
    Dealokasi(&P);  
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P){
  Next(P) = First(*L);
  First(*L) = P;
}

void InsertAfter (List *L, address P, address Prec){
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void InsertLast (List *L, address P){
  address Last;

  if (IsEmpty(*L)) {
    InsertFirst(L, P);
  } else {
    Last = First(*L);
    while (Next(Last) != Nil) {
      Last = Next(Last);
    }
    InsertAfter(L, P, Last);
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P){
    *P=First(*L);
    First(*L)=Next(First(*L));
    Next(*P)=Nil;
}

void DelP (List *L, infotype X){
    if (!IsEmpty(*L)) {
        address P = Search(*L, X);
        if (P != Nil) {
            if (P == First(*L)) {
                First(*L) = Next(P);
                Next(P) = Nil;
                Dealokasi(&P);
            } else {
                address Prec = First(*L);
                while (Next(Prec) != P) {
                    Prec = Next(Prec);
                }
                DelAfter(L, &P, Prec);
                Dealokasi(&P);
            }
        }
    }
}

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

void DelAfter (List *L, address *Pdel, address Prec){
    *Pdel=Next(Prec);
    Next(Prec)=Next(Next(Prec));
    Next(*Pdel)=Nil;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L){
  address P;
  boolean isFirst = true;

  printf("[");
  if (!IsEmpty(L)) {
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

int NbElmt (List L){
    address P;
    int count=0;

    if(!IsEmpty(L)){
        P=First(L);
        while (P!=Nil){
            count+=1;
            P=Next(P);
        }
    }

    return count;
}

infotype Min (List L){
    address P=Next(First(L));
    infotype min=Info(First(L));

    while(P!=Nil){
        if (Info(P)<min)
            min=Info(P);
        P=Next(P);
    }

    return min;
}

infotype Max (List L)
{
    infotype max=Info(First(L));
    address P=Next(First(L));

    while(P!=Nil){
        if (Info(P)>max)
            max=Info(P);
        P=Next(P);
    }

    return max;
}

/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3){
    address Last;

    CreateEmpty(L3);
    if (IsEmpty(*L1))
        First(*L3)=First(*L2);
    else{
        First(*L3)=First(*L1);
        Last=First(*L1);
        while (Next(Last)!=Nil)
            Last=Next(Last);
        Next(Last)=First(*L2);
    }

    First(*L1)=Nil;
    First(*L2)=Nil;
}