// Driver tree
// 13519206 / Muhammad Fawwaz Naabigh
#include "../tree.h"
#include <stdio.h>

int main(){
    addrNode L1 = AlokNode(5);
    addrNode R1 = AlokNode(4);
    BinTree L = Tree(1, L1, R1);
    BinTree R = Tree(2, L1, R1);
    AddDaun(&R, 5, 6, false);
    BinTree P = Tree(8, L, R);
    PrintTree(P, 4);

    DelDaun(&R, 6);
    printf("Pohon setelah daun dihapus\n");
    PrintTree(P, 4);
    AddDaun(&R, 8, 4, true);
    printf("\n");
    printf("Banyak elemen adalah %d\n", NbElmt(P));
    printf("Banyak daun adalah %d\n", NbDaun(P));
    printf("Level node '1' adalah %d\n", Level(P, 1));
    printf("Tinggi pohon adalah %d\n", Tinggi(P));
    printf("Node berlevel 3:\n");
    PrintList(MakeListLevel(P, 3));
    printf("Semua daun:\n");
    PrintList(MakeListDaun(P));
    printf("Semua node:\n");
    PrintList(MakeListPreorder(P));

    if(SearchTree(P, 5)){
        printf("5 ada di pohon\n");
    }
    if(IsBiner(P)){
        printf("Ini adalah pohon biner");
    }
    if(IsUnerLeft(P)){
        printf("Ini adalah pohon uner dengan subpohon di kiri");
    }
    if(IsUnerRight(P)){
        printf("Ini adalah pohon uner dengan subpohon di kanan");
    }
    return 0;
}
