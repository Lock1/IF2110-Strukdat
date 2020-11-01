/* 13519214
----- Self note -----
Useful UTF-8 Char for map
\u2588 -> Solid block
*/

// Library
#include "engine.h"

// -------- Variable Declaration & Initialization --------
char frame[RES_Y][RES_X];
char nframe[RES_Y][RES_X];

const short int cRestX = 60;
const short int cRestY = 27;

char mapframe[MAP_SIZE_Y][MAP_SIZE_X];
// TODO : Information interface
// Player name (line 1)
// Money (line 2)
// Time (line 3-5) (start, elapsed, stop)
// Queue (line 6-12) (2 line for border, 5 for actual queue)
// Broken building (line 13-15)
// -------------------------------------------------------


// ---------------- Function Definition =-----------------

// Theres function in Windows that allow set cursor pos
// Linux implementation pretty short
void setCursorPosition(int XPos, int YPos) {
    printf("\033[%d;%dH",YPos+1,XPos+1);
}
// TODO : Update


void mapUpdate() {
    // TODO : Need actual matrix of building to properly update
    // FIXME : Theres 2 pixel getting changed at same time
    // DEBUG
    if (random()%2)
        mapframe[random()%MAP_SIZE_Y][random()%MAP_SIZE_X] = 43;
    else
        mapframe[random()%MAP_SIZE_Y][random()%MAP_SIZE_X] = 79;
    // DEBUG STOP
    for (int i = 0 ; i < MAP_SIZE_Y ; i++)
        for (int j = 0 ; j < MAP_SIZE_X ; j++)
            nframe[MAP_OFFSET_Y+i][MAP_OFFSET_X+j] = mapframe[i][j];
}


// Engine implementation
void frameSet() { // TODO : Possible merge with other frame function
    // DEBUG
    for (int i = 0 ; i < RES_Y ; i++)
        for (int j = 0 ; j < RES_X ; j++)
            nframe[i][j] = frame[i][j] = '|';
    for (int i = 0 ; i < MAP_SIZE_Y ; i++)
        for (int j = 0 ; j < RES_X ; j++)
            mapframe[i][j] = '-';

    char topb[] = "____________________/   Map   \\_____________________";
    char botb[] = "\\__________________________________________________/";
    for (int i = 0 ; i < 52 ; i++) {
        nframe[MAP_OFFSET_Y-1][MAP_OFFSET_X-1+i] = topb[i];
        nframe[MAP_OFFSET_Y+MAP_SIZE_Y][MAP_OFFSET_X-1+i] = botb[i];
    }
    // DEBUG STOP
}

// TODO : Maybe special UTF-8 draw

void forceDraw() {
    system(CLSCRN);
    fflush(stdout);
    setCursorPosition(0,0);
    for (int i = 0 ; i < RES_Y ; i++) {
        for (int j = 0 ; j < RES_X ; j++) {
            // Remember index are flipped
            setCursorPosition(j,i);
            // DEBUG
            // dpf("%s","\u2588");
            // DEBUG STOP
            putchar(nframe[i][j]);
        }
        puts("");
    }
    setCursorPosition(cRestX,cRestY);
}

void draw(){
    fflush(stdout);
    // DEBUG
    int s = random()%RES_Y;
    int p = random()%RES_X;
    if (((s > (MAP_SIZE_Y+MAP_OFFSET_Y)) || (s < (MAP_OFFSET_Y-1))) || ((p > (MAP_SIZE_X+MAP_OFFSET_X)) || (p < (MAP_OFFSET_X-1))))
        nframe[s][p] = 65 + random()%6;
    // DEBUG STOP
    setCursorPosition(0,0);
    for (int i = 0 ; i < RES_Y ; i++)
        for (int j = 0 ; j < RES_X ; j++)
            if (nframe[i][j] != frame[i][j]) {
                // Remember index are flipped
                setCursorPosition(j,i);
                putchar(nframe[i][j]);
                frame[i][j] = nframe[i][j];
            }
    setCursorPosition(cRestX,cRestY);
}
// -------------------------------------------------------
