// Nama : Dwianditya Hanif
// NIM : 13519046
// Tanggal : 30 September 2020
// Topik : Mesin Kata
// Deskripsi : Implementasi driver-mesinkata.c
#include "../mesinkata.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    wordInput();
    int i=0;
    while(!EndKata){
        for(i=0;i<CKata.Length;i++){
            printf("%c", CKata.TabKata[i]);
        }
        printf(" ");
        IgnoreBlank();
        ADVKATA();
    }
}

// gcc drvier_mkata.c mesinkata.c mesinkar.c -o a
