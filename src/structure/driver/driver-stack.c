// Driver stack
// 13519206 / Muhammad Fawwaz Naabigh
#include "../stack.h"
#include <stdio.h>

int main(){
    Stack S;
    CreateEmpty(&S);
    infotype X;
    if(IsEmpty(S)){
        for(int i = 0;i<5;i++){
            infotype aa;
            aa.actID = i*1;
            aa.entityID = i*2;
            aa.eventPosX = i*3;
            aa.eventPosY = i*4;
            aa.actIdentifier = i*5;
            aa.actionMap = i*6;
            Push(&S, aa);
            printf("Value stack yg dipush adalah %d\n", aa.actID);
            printf("Value stack yg dipush adalah %d\n", aa.entityID);
            printf("Value stack yg dipush adalah %d\n", aa.eventPosX);
            printf("Value stack yg dipush adalah %d\n", aa.eventPosY);
            printf("Value stack yg dipush adalah %d\n", aa.actIdentifier);
            printf("Value stack yg dipush adalah %d\n", aa.actionMap);
        }
    }
    while (!IsEmpty(S)){
        Pop(&S, &X);
        printf("Value stack yg dipop adalah %d\n", X.actID);
        printf("Value stack yg dipop adalah %d\n", X.entityID);
        printf("Value stack yg dipop adalah %d\n", X.eventPosX);
        printf("Value stack yg dipop adalah %d\n", X.eventPosY);
        printf("Value stack yg dipop adalah %d\n", X.actIdentifier);
        printf("Value stack yg dipop adalah %d\n", X.actionMap);
    }

    return 0;
}
