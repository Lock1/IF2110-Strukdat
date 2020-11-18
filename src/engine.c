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
char infoframe[INFO_SIZE_Y][INFO_SIZE_X];

char username[STRING_LENGTH] = "";
int money = START_MONEY;
// TODO : set time

// -------------------------------------------------------


// ---------------- Function Definition =-----------------

// Theres function in Windows that allow set cursor pos
// Linux implementation pretty short
void setCursorPosition(int XPos, int YPos) {
    printf("\033[%d;%dH",YPos+1,XPos+1);
}
// TODO : Update

// TODO : comment
void stringCopy(char src[STRING_LENGTH], char dst[STRING_LENGTH]) {
    for (int i = 0 ; src[i] != '\0' ; i++)
        dst[i] = src[i]; // FIXME : maybe null terminator
}

// TODO : comment
boolean stringCompare(char st1[STRING_LENGTH], char st2[STRING_LENGTH]) {
    for (int i = 0 ; st1[i] != '\0' ; i++)
        if (st1[i] != st2[i])
            return false;
    return true;
}

// TODO : Fix this
void infoUpdate() {
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (username[i] == '\0')
            break;
        else
            infoframe[0][INFO_BLOCK_SIZE+i+1] = username[i];

    char moneyString[INFO_SIZE_X - INFO_BLOCK_SIZE];
    sprintf(moneyString,"%d",money);
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (moneyString[i] == '\0')
            break;
        else
            infoframe[1][INFO_BLOCK_SIZE+i+1] = moneyString[i];
    // TODO : money

    // DEBUG
    // if (random()%2)
    //     infoframe[random()%INFO_SIZE_Y][random()%INFO_SIZE_X] = 41;
    // else
    //     infoframe[random()%INFO_SIZE_Y][random()%INFO_SIZE_X] = 79;




    // DEBUG STOP
    for (int i = 0 ; i < INFO_SIZE_Y ; i++)
        for (int j = 0 ; j < INFO_SIZE_X ; j++)
            nframe[INFO_OFFSET_Y+i][INFO_OFFSET_X+j] = infoframe[i][j];
}

// TODO : cleanup
boolean startGame() {
    puts(START_MENU_ASCII_ART);
    puts("1. New Game");
    // puts("2. Continue");
    // puts("3. Load game");
    puts("2. Quit");

    printf(">> ");
    wordInput();
    // char userInput[STRING_LENGTH];
    // stringCopy(CurrentInput,userInput);
    if (stringCompare("new",CurrentInput) || CurrentInput[0] == '1') {
        printf("Masukkan nama : ");
        wordInput();
        stringCopy(CurrentInput,username);
        puts(HAVE_FUN_ASCII_ART);
        puts(WILLY_WANGKY_ASCII_ART);
        return true;
    }
    else if (stringCompare("quit", CurrentInput) || CurrentInput[0] == '2')
        return false;
    return false;
}
// TODO : Load branch


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

// Delaying by counting
void delay(int limit) {
    long long int clock = 0, count = 0;
    while (count != limit) {
        while (clock != IC)
            clock++;
        clock = 0;
        count++;
    }
}



// Engine implementation
void frameSet() { // TODO : Possible merge with other frame function
    // DEBUG
    for (int i = 0 ; i < RES_Y ; i++)
        for (int j = 0 ; j < RES_X ; j++)
            nframe[i][j] = frame[i][j] = '\0';
    for (int i = 0 ; i < MAP_SIZE_Y ; i++)
        for (int j = 0 ; j < RES_X ; j++)
            mapframe[i][j] = '-';
    for (int i = 0 ; i < INFO_SIZE_Y ; i++)
        for (int j = 0 ; j < INFO_SIZE_X ; j++)
            infoframe[i][j] = '\0';

    char *infoBlock[8];
    infoBlock[0] = "Nama           | ";
    infoBlock[1] = "Money          | ";
    infoBlock[2] = "Current time   | ";
    infoBlock[3] = "Closing time   | ";
    infoBlock[4] = "Time remaining | ";
    infoBlock[5] = "     ---------------- Queue -----------------     ";
    infoBlock[6] = "     ----------------------------------------     ";
    infoBlock[7] = "           ----- Broken Building -----            ";
    for (int i = 0 ; i < 5 ; i++)
        for (int j = 0 ; j < INFO_BLOCK_SIZE ; j++)
            infoframe[i][j] = infoBlock[i][j];

    // char queue[] = "     ---------------- Queue -----------------     ";
    for (int i = 0 ; i < INFO_SIZE_X ; i++) {
        infoframe[5][i] = infoBlock[5][i];
        infoframe[11][i] = infoBlock[6][i];
        infoframe[12][i] = infoBlock[7][i];
    }
    // char qb[] = "     ----------------------------------------     ";
    // for (int i = 0 ; i < 50 ; i++)
    //     infoframe[11][i] = qb[i];
    // char bb[] = "ajur nggeh";
    // for (int i = 0 ; i < 15 ; i++)
    //     infoframe[12][i] = bb[i];


    char topb[] = "____________________/   Map   \\_____________________";
    char botb[] = "\\__________________________________________________/";
    for (int i = 0 ; i < 52 ; i++) {
        nframe[MAP_OFFSET_Y-1][MAP_OFFSET_X-1+i] = topb[i];
        nframe[MAP_OFFSET_Y+MAP_SIZE_Y][MAP_OFFSET_X-1+i] = botb[i];
    }
    char infotb[] = "____________________/   Info   \\____________________";
    char infobb[] = "\\__________________________________________________/";

    for (int i = 0 ; i < 53 ; i++) {
        nframe[INFO_OFFSET_Y-1][INFO_OFFSET_X-1+i] = infotb[i];
        nframe[INFO_OFFSET_Y+INFO_SIZE_Y][INFO_OFFSET_X-1+i] = infobb[i];
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
    // int s = random()%RES_Y;
    // int p = random()%RES_X;
    // if (((s > (MAP_SIZE_Y+MAP_OFFSET_Y)) || (s < (MAP_OFFSET_Y-1))) || ((p > (MAP_SIZE_X+MAP_OFFSET_X)) || (p < (MAP_OFFSET_X-1))))
    //     nframe[s][p] = 65 + random()%6;
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
