// ADT Tree
// 13519206 / Muhammad Fawwaz Naabigh
#include "tree.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

/* *** PROTOTYPE *** */

/* *** Konstruktor *** */
BinTree Tree (listrekInfotype Akar, BinTree L, BinTree R)
{
    BinTree P = (BinTree)malloc(sizeof(BinTree));
    if(P!=ListNil){
        Akar(P) = Akar;
        Left(P) = L;
        Right(P) = R;
    }
    return P;
}


void MakeTree (listrekInfotype Akar, BinTree L, BinTree R, BinTree *P)
{
    *P = Tree(Akar, L, R);
}

/* Manajemen Memory */
addrNode AlokNode (listrekInfotype X)
{
    addrNode P = (addrNode)malloc(sizeof(Node));
    if(P!=ListNil){
        Akar(P) = X;
        Left(P) = ListNil;
        Right(P) = ListNil;
    }
    return P;
}

void DealokNode (addrNode P)
{
    free(P);
}

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty (BinTree P)
{
    return P == ListNil;
}

boolean IsTreeOneElmt (BinTree P)
{
    return (!IsTreeEmpty(P))?(Left(P)==ListNil && Right(P)==ListNil): false;
}

boolean IsUnerLeft (BinTree P)
{
    return (!IsTreeEmpty(P))?(Left(P)!=ListNil && Right(P)==ListNil): false;
}

boolean IsUnerRight (BinTree P)
{
   return (!IsTreeEmpty(P))?(Left(P)==ListNil && Right(P)!=ListNil): false;
}

boolean IsBiner (BinTree P)
{
   return (!IsTreeEmpty(P))?(Left(P)!=ListNil && Right(P)!=ListNil): false;
}

void PrintTree(BinTree P, int h)
{
   if(!IsTreeEmpty(P)){
      printf("%d\n", Akar(P));
      if(Left(P)!=ListNil){
         for(int i = 0;i<h;i++){
            printf(" ");
         }
         PrintTree(Left(P), h+h);
      }
      if(Right(P)!=ListNil){
         for(int i = 0;i<h;i++){
            printf(" ");
         }
         PrintTree(Right(P), h+h);
      }
   }
}

/* *** Searching *** */
boolean SearchTree (BinTree P, listrekInfotype X)
/* Mengirimkan true jika ada node dari P yang berListListNilai X */
{
   if(IsTreeEmpty(P)) return false;
   else if(Akar(P)!=X) return ((SearchTree(Left(P), X)) || (SearchTree(Right(P), X)));
   else return true;
}

/* *** Fungsi-Fungsi Lain *** */
int NbElmt (BinTree P)
{
   return (IsTreeEmpty(P))? 0: (NbElmt(Left(P))+NbElmt(Right(P))+1);
}

int NbDaun (BinTree P)
{
   if(IsTreeEmpty(P)) return 0;
   else if(IsTreeOneElmt(P)) return 1;
   else return (NbDaun(Left(P))+NbDaun(Right(P)));
}


int Level (BinTree P, listrekInfotype X)
{
   if(SearchTree(Left(P), X)) return 1+Level(Left(P), X);
   else if(SearchTree(Right(P), X)) return 1+Level(Right(P), X);
   else return 1;
}

int Tinggi (BinTree P)
{
   if(IsTreeEmpty(P)) return 0;
   else {
      int Tinggi_L = Tinggi(Left(P));
      int Tinggi_R = Tinggi(Right(P));
      return (Tinggi_L>Tinggi_R)? Tinggi_L+1 : Tinggi_R+1;
   }
}

/* *** Operasi lain *** */
void AddDaunTerkiri (BinTree *P, listrekInfotype X)
{

   if(IsTreeEmpty(*P)) 
      *P = Tree(X, ListNil, ListNil);
   else AddDaunTerkiri(&Left(*P), X);
}

void AddDaun (BinTree *P, listrekInfotype X, listrekInfotype Y, boolean Kiri)
{
   if(IsTreeOneElmt(*P)&&Akar(*P)==X){
      if(Kiri) Left(*P)=Tree(Y, ListNil, ListNil);
      else Right(*P)=Tree(Y, ListNil, ListNil);
   }
   else{
      if(SearchTree(Left(*P), X)) AddDaun(&Left(*P), X, Y, Kiri);
      else if(SearchTree(Right(*P), X)) AddDaun(&Right(*P), X, Y, Kiri);
   }
}

void DelDaun (BinTree *P, listrekInfotype X)
{
    if(!IsTreeEmpty(*P)){
        if(IsTreeOneElmt(*P) && Akar(*P)==X){
            addrNode tmp = *P;
            *P = ListNil;
            DealokNode(tmp);
        }
        else{
            DelDaun(&Left(*P), X);
            DelDaun(&Right(*P), X);
        }
    }
}

List MakeListDaun (BinTree P)
{
    if(IsTreeEmpty(P)) return ListNil;
    else if(IsTreeOneElmt(P)) return Alokasi(Akar(P));
    else{
        List Kiri = MakeListDaun(Left(P));
        List Kanan = MakeListDaun(Right(P));
        return Concat(Kiri, Kanan);
    }
}

List MakeListPreorder (BinTree P)
{
   if(IsTreeEmpty(P)) return ListNil;
   else{
      List Kiri = MakeListPreorder(Left(P));
      List Kanan = MakeListPreorder(Right(P));
      return Concat(Konso(Akar(P), Kiri), Kanan);
   }
}

List MakeListLevel (BinTree P, int N)
{
   if(IsTreeEmpty(P)) return ListNil;
   else if (N==1) return Alokasi(Akar(P));
   else{
      List Kiri = MakeListLevel(Left(P), N-1);
      List Kanan = MakeListLevel(Right(P), N-1);
      return Concat(Kiri, Kanan);
   }
}
