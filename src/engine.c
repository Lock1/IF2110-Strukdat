/* 13519214
----- Self note -----
Useful UTF-8 Char for map
\u2588 -> Solid block
*/

// Library
#include "engine.h"

// -------- Variable Declaration & Initialization --------
char frames[20][20];    // Everything inside frame, temporary for debugging only 20
char nframe[20][20];
const int cRestX = 24;
const int cRestY = 21;
// -------------------------------------------------------


// ---------------- Function Definition =-----------------

// Theres function in Windows that allow set cursor pos
// Linux implementation pretty short
void setCursorPosition(int XPos, int YPos) {
    printf("\033[%d;%dH",YPos+1,XPos+1);
}


// Engine implementation
void forceDraw() {
    fflush(stdout);
    setCursorPosition(0,0);
    for (int i = 0 ; i < 20 ; i++) {
        for (int j = 0 ; j < 20 ; j++)
            printf("%c",nframe[i][j]);
        printf("\n");
    }
    setCursorPosition(cRestX,cRestY);
}

void draw(){
    fflush(stdout);
    setCursorPosition(0,0);
    for (int i = 0 ; i < 20 ; i++)
        for (int j = 0 ; j < 20 ; j++)
            if (nframe[i][j] != frames[i][j]) {
                setCursorPosition(i,j);
                printf("%c",nframe[i][j]);
                frames[i][j] = nframe[i][j];
            }
    setCursorPosition(cRestX,cRestY);
}
// -------------------------------------------------------
