// Driver stack
// 13519206 / Muhammad Fawwaz Naabigh
#include "../stack.h"
#include <stdio.h>

int main(){
    Stack S;
    CreateEmpty(&S);
    int X;
    if(IsEmpty(S)){
        for(int i = 0;i<10;i++){
            Push(&S, i);
            printf("Value stack yg dipush adalah %d\n", i);
        }
    }
    while (!IsEmpty(S)){
        Pop(&S, &X);
        printf("Value stack yg dipop adalah %d\n", X);
    }

    return 0;
}
