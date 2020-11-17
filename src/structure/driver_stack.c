#include "stack.h"
#include <stdio.h>

int main(){
    Stack S;
    CreateEmpty(&S);
    int X;
    if(IsEmpty(S)){
        for(int i = 0;i<10;i++){
            Push(&S, i);
            printf("value stack yg dipush adalah %d\n", i);
        }
    }
    if(IsFull(S)){
        Pop(&S, &X);
    }
    printf("value stack yg dipop adalah %d\n", X);
    
    return 0;
}