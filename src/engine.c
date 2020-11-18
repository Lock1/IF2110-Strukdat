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

JAM playTime;
JAM prepTime;

char mapframe[MAP_SIZE_Y][MAP_SIZE_X];
char infoframe[INFO_SIZE_Y][INFO_SIZE_X];

char username[STRING_LENGTH] = "";
int money = START_MONEY;
int currentDay = 1;
JAM currentTime;
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

    char dayString[INFO_SIZE_X - INFO_BLOCK_SIZE];
    sprintf(dayString,"%d",currentDay);
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (dayString[i] == '\0')
            break;
        else
            infoframe[2][INFO_BLOCK_SIZE+i+1] = dayString[i];

    char tempTime[STRING_LENGTH], curTime[STRING_LENGTH];
    sprintf(tempTime,"%d",Hour(currentTime));
    stringCopy(tempTime,curTime);
    curTime[2] = ':';
    sprintf(tempTime,"%d",Minute(currentTime));
    if (Minute(currentTime) < 10) {
        curTime[3] = '0';
        curTime[4] = tempTime[0];
    }
    else {
        curTime[3] = tempTime[0];
        curTime[4] = tempTime[1];
    }
    curTime[5] = '\0';
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (curTime[i] == '\0')
            break;
        else
            infoframe[3][INFO_BLOCK_SIZE+i+1] = curTime[i];

    // DEBUG

    // DEBUG END

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
        playTime = MakeJAM(START_PLAY,0);
        prepTime = MakeJAM(START_PREP,0);
        currentTime = MakeJAM(START_PREP,0);
        return true;
    }
    else if (stringCompare("quit", CurrentInput) || CurrentInput[0] == '2')
        return false;
    return false;
}
// TODO : Load branch

void prepDay() {
    frameSet(1);
    // forceDraw();
    // unicodeDraw(0);
    // while (true) {
    //
    // }
}



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
void frameSet(int tp) { // TODO : Possible merge with other frame function
    // 0 Initialization
    // 1 Preparation
    // 2 Play

    // DEBUG
    if (tp == 0) {
        for (int i = 0 ; i < RES_Y ; i++)
            for (int j = 0 ; j < RES_X ; j++)
                nframe[i][j] = frame[i][j] = '\0';
        for (int i = 0 ; i < MAP_SIZE_Y ; i++)
            for (int j = 0 ; j < RES_X ; j++)
                mapframe[i][j] = '-';
        for (int i = 0 ; i < INFO_SIZE_Y ; i++)
            for (int j = 0 ; j < INFO_SIZE_X ; j++)
                infoframe[i][j] = '\0';
    }

    char *infoBlock[9];
    infoBlock[0] = "Nama           | ";
    infoBlock[1] = "Money          | ";
    infoBlock[2] = "Day            | ";
    infoBlock[3] = "Current time   | ";
    if (tp == 1 || tp == 0)
        infoBlock[4] = "Opening time   | ";
    else if (tp == 2)
        infoBlock[4] = "Closing time   | ";
    infoBlock[5] = "Time remaining | ";
    if (tp == 1 || tp == 0)
        infoBlock[6] = "     --------------- Action -----------------     ";
    else if (tp == 2)
        infoBlock[6] = "     ---------------- Queue -----------------     ";
    infoBlock[7] = "     ----------------------------------------     ";
    infoBlock[8] = "           ----- Broken Building -----            ";
    for (int i = 0 ; i < 6 ; i++)
        for (int j = 0 ; j < INFO_BLOCK_SIZE ; j++)
            infoframe[i][j] = infoBlock[i][j];

    for (int i = 0 ; i < INFO_SIZE_X ; i++) {
        infoframe[6][i] = infoBlock[6][i];
        infoframe[12][i] = infoBlock[7][i];
        infoframe[13][i] = infoBlock[8][i];
    }


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


void unicodeDraw(int tp) {
    switch (tp) {
        case 0:
            setCursorPosition(INFO_OFFSET_X,INFO_OFFSET_Y-4);
            puts(PREP_DAY_TITLE_1);
            setCursorPosition(INFO_OFFSET_X,INFO_OFFSET_Y-3);
            puts(PREP_DAY_TITLE_2);
            break;
        case 1:

            break;
    }
}




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
