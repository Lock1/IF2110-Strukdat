// Driver linked list
// 13519146 / Fadel Ananda Dotty
#include <stdio.h>
#include <stdlib.h>
#include "../listlinear.h"

int main(){
    List L;
    int X;
    CreateEmpty(&L);
    InsVLast(&L, 1);
    InsVLast(&L, 2);
    InsVLast(&L, 3);
    DelVLast(&L, &X);
    printf("%d", X);
    return 0;
}
