/* File : mjam.c */
/* Program MainJam */
/* Driver ADT Jam */
#include <stdio.h>
#include "jam.h"
#include "boolean.h"

int main()
{   /* KAMUS */
    JAM J1, J2;
    /* ALGORITMA */
    BacaJAM(&J1);
    printf("Jam sekarang: ");
    TulisJAM(J1); printf("\n");
    printf("Konversi menjadi menit: %d\n",JAMToMenit(J1));
    J2 = MenitToJAM(5000);
    printf("5000 menit sama dengan jam : ");
    TulisJAM(J2); printf("\n");
    

    
    printf("10 menit setelah J1 adalah ");
    TulisJAM(NextNMenit(J1, 10));
    printf("\n");
    printf("Durasi dari J1 dan J2 adalah %ld menit", Durasi(J1, J2));

    return 0;
}


 