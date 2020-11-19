/* 13519214
----- Self note -----
Useful UTF-8 Char for map
\u2588 -> Solid block

Internal reference in engine.c
Preparation phase -> Prep
Main phase -> Play

*/



// Library
#include "engine.h"

// -------- Variable Declaration & Initialization --------
char frame[RES_Y][RES_X];
char nframe[RES_Y][RES_X];

const short int cRestX = 60;
const short int cRestY = 27;

JAM cPlayTime;
JAM cPrepTime;

char mapframe[MAP_SIZE_Y][MAP_SIZE_X];
char infoframe[INFO_SIZE_Y][INFO_SIZE_X];

matrix map1, map2, map3, map4;
POINT cursorLocation;
POINT playerLocation;
char username[STRING_LENGTH] = "";
int money = START_MONEY;
int currentDay = 1;
int buildingCount = 0;
int materialCount = 0;
JAM currentTime;
Stack actionStack;
int actionCount = 0;

Wahana* buildingDatabase;
Material* materialDatabase;


// -------------------------------------------------------


// ---------------- Function Definition =-----------------

// ----- Other function -----
// Theres function in Windows that allow set cursor pos
// Anyway UNIX implementation pretty short
void setCursorPosition(int XPos, int YPos) {
    printf("\033[%d;%dH",YPos+1,XPos+1);
}

void stringCopy(char src[STRING_LENGTH], char dst[STRING_LENGTH]) {
    for (int i = 0 ; src[i] != '\0' ; i++)
        dst[i] = src[i]; // FIXME : maybe null terminator
}

boolean stringCompare(char st1[STRING_LENGTH], char st2[STRING_LENGTH]) {
    for (int i = 0 ; st1[i] != '\0' ; i++)
        if (st1[i] != st2[i])
            return false;
    return true;
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





// ----- Load function -----
void loadMap() {
    // TODO : Load actual map.txt
    makeMatrix(MAP_SIZE_X,MAP_SIZE_Y,&map1);
    makeMatrix(MAP_SIZE_X,MAP_SIZE_Y,&map2);
    makeMatrix(MAP_SIZE_X,MAP_SIZE_Y,&map3);
    makeMatrix(MAP_SIZE_X,MAP_SIZE_Y,&map4);
    for (int i = 0 ; i < rowLen(map1) ; i++) {
        for (int j = 0 ; j < colLen(map1) ; j++) {
            occupiedAt(map1,i,j) = occupiedAt(map2,i,j) = occupiedAt(map3,i,j) = occupiedAt(map4,i,j) = false;
            entityAt(map1,i,j) = entityAt(map2,i,j) = entityAt(map3,i,j) = entityAt(map4,i,j) = 0;
            buildingAt(map1,i,j) = buildingAt(map2,i,j) = buildingAt(map3,i,j) = buildingAt(map4,i,j) = NULL;
        }
    }

}

void loadDatabase() {
    buildingCount = ReadFromWahana(&buildingDatabase);
    materialCount = ReadFromBahan(&materialDatabase);
}





// ----- Frame update function -----
void infoUpdate(int tp) {

    // ---- Wipe ----
    // Money frame wipe
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
            infoframe[1][INFO_BLOCK_SIZE+i] = ' ';

    // ---- Username ---
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (username[i] == '\0')
            break;
        else
            infoframe[0][INFO_BLOCK_SIZE+i+1] = username[i];
    // ---- Money ----
    char moneyString[INFO_SIZE_X - INFO_BLOCK_SIZE];
    sprintf(moneyString,"%d",money);
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (moneyString[i] == '\0')
            break;
        else
            infoframe[1][INFO_BLOCK_SIZE+i+1] = moneyString[i];
    // ---- Day ----
    char dayString[INFO_SIZE_X - INFO_BLOCK_SIZE];
    sprintf(dayString,"%d",currentDay);
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (dayString[i] == '\0')
            break;
        else
            infoframe[2][INFO_BLOCK_SIZE+i+1] = dayString[i];
    // ---- Current time ----
    char tempTime[STRING_LENGTH], curTime[STRING_LENGTH];
    // Hour Handler
    sprintf(tempTime,"%d",Hour(currentTime));
    if (Hour(currentTime) < 10) {
        curTime[0] = '0';
        curTime[1] = tempTime[0];
    }
    else {
        curTime[0] = tempTime[0];
        curTime[1] = tempTime[1];
    }
    // Separator
    curTime[2] = ':';
    // Minute Handler
    sprintf(tempTime,"%d",Minute(currentTime));
    if (Minute(currentTime) < 10) {
        curTime[3] = '0';
        curTime[4] = tempTime[0];
    }
    else {
        curTime[3] = tempTime[0];
        curTime[4] = tempTime[1];
    }
    // Copying and null terminator
    curTime[5] = '\0';
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (curTime[i] == '\0')
            break;
        else
            infoframe[3][INFO_BLOCK_SIZE+i+1] = curTime[i];

    // ---- Time remaining ----
    char timeRemaining[STRING_LENGTH];
    JAM targetTime;
    // Hour Handler
    if (tp == 0 || tp == 1)
        targetTime = MenitToJAM(Durasi(currentTime,cPlayTime));
    else if (tp == 2)
        targetTime = MenitToJAM(Durasi(currentTime,cPrepTime));
    sprintf(tempTime,"%d", Hour(targetTime));
    if (Hour(targetTime) < 10) {
        timeRemaining[0] = '0';
        timeRemaining[1] = tempTime[0];
    }
    else {
        timeRemaining[0] = tempTime[0];
        timeRemaining[1] = tempTime[1];
    }
    // Separator
    timeRemaining[2] = ':';
    // Minute Handler
    sprintf(tempTime,"%d",Minute(targetTime));
    if (Minute(targetTime) < 10) {
        timeRemaining[3] = '0';
        timeRemaining[4] = tempTime[0];
    }
    else {
        timeRemaining[3] = tempTime[0];
        timeRemaining[4] = tempTime[1];
    }
    // Copying and null terminator
    timeRemaining[5] = '\0';
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
        if (timeRemaining[i] == '\0')
            break;
        else
            infoframe[5][INFO_BLOCK_SIZE+i+1] = timeRemaining[i];

    // Moving info frame to next frame buffer
    for (int i = 0 ; i < INFO_SIZE_Y ; i++)
        for (int j = 0 ; j < INFO_SIZE_X ; j++)
            nframe[INFO_OFFSET_Y+i][INFO_OFFSET_X+j] = infoframe[i][j];
}

void mapUpdate(int tp) {
    // DEBUG
    for (int i = 0 ; i < MAP_SIZE_Y ; i++)
        for (int j = 0 ; j < MAP_SIZE_X ; j++)
            switch (entityAt(map1,i,j)) {
                case 0:
                    mapframe[i][j] = '.'; // Nothing
                    break;
                case 1:
                    mapframe[i][j] = '@'; // Player
                    break;
                default:
                    if (entityAt(map1,i,j) > 19)
                        mapframe[i][j] = buildingAt(map1,i,j)->gambar;
                    break;
            }
    // Draw cursor only on preparation phase
    if (tp == 1)
        mapframe[Ordinat(cursorLocation)][Absis(cursorLocation)] = '*';

     // TODO : Let unique UNICODE char print as '*' at background
    // if (random()%2)
    //     mapframe[random()%MAP_SIZE_Y][random()%MAP_SIZE_X] = 43;
    // else
    //     mapframe[random()%MAP_SIZE_Y][random()%MAP_SIZE_X] = 79;
    // DEBUG STOP
    for (int i = 0 ; i < MAP_SIZE_Y ; i++)
        for (int j = 0 ; j < MAP_SIZE_X ; j++)
            nframe[MAP_OFFSET_Y+i][MAP_OFFSET_X+j] = mapframe[i][j];
}





// ----- Game function -----
boolean startGame() {
    puts(START_MENU_ASCII_ART);
    puts("1. New Game");
    // puts("2. Continue"); // TODO : Bonus
    // puts("3. Load game");
    puts("2. Quit");

    printf(">> ");
    wordInput();
    if (stringCompare("new",CurrentInput) || CurrentInput[0] == '1') {
        // Name prompt and ASCII art
        printf("Masukkan nama : ");
        wordInput();
        stringCopy(CurrentInput,username);
        puts(HAVE_FUN_ASCII_ART);
        puts(WILLY_WANGKY_ASCII_ART);

        // Variable Initialization
        CreateEmpty(&actionStack);
        loadMap();
        loadDatabase();
        cPlayTime = MakeJAM(START_PLAY,0);
        cPrepTime = currentTime = MakeJAM(START_PREP,0);
        cursorLocation = MakePOINT(CURSOR_REST_X,CURSOR_REST_Y);
        playerLocation = MakePOINT(PLAYER_START_X,PLAYER_START_Y);
        occupiedAt(map1,PLAYER_START_X,PLAYER_START_Y) = true;
        entityAt(map1,PLAYER_START_X,PLAYER_START_Y) = 1;

        return true;
    }
    else if (stringCompare("quit", CurrentInput) || CurrentInput[0] == '2')
        return false;
    return false;
}
// TODO : Move between map
void prepDay() {
    // Preparation day references
    /* Undo table
    | ActID | Action |
    | ----- | ------ |
    | 1     | Build  |
    | 2     | Upgrade|
    | 3     | Buy    |
    | -------------- |
    Every action logged on actionTuple,
    check stack.h for more information
    */
    frameSet(1);
    unicodeDraw(1);
    Absis(cursorLocation) = CURSOR_REST_X;
    Ordinat(cursorLocation) = CURSOR_REST_Y;
    // Preparation day loop
    while (true) {
        infoUpdate(1);
        mapUpdate(1);
        draw();

        // Positioning for user input
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
        wordInput();
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
        puts("                   ");
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
        puts("                                                 ");
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);

        // Input check
        if (stringCompare("build",CurrentInput)) {
            boolean isAreaBuildable = !occupiedAt(map1,Ordinat(cursorLocation),Absis(cursorLocation));
            if (isAreaBuildable) {
                printBuildList();
                wordInput(); // WARNING : BUILDING ID START FROM 20
                int tempID;
                sscanf(CurrentInput,"%d",&tempID);
                setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+2);
                if (searchWahanaByID(buildingDatabase,tempID+19)) {
                    int buildCost = getHargaWahanaByID(buildingDatabase,tempID+19);
                    if (money >= buildCost) {
                        actionTuple buildLog = { 1,tempID+19,Ordinat(cursorLocation),Absis(cursorLocation),buildCost };
                        Push(&actionStack,buildLog);
                        currentTime = NextNMenit(currentTime,BUILD_TIME); // Build time
                        occupiedAt(map1,Ordinat(cursorLocation),Absis(cursorLocation)) = true;
                        entityAt(map1,Ordinat(cursorLocation),Absis(cursorLocation)) = tempID+19;
                        buildingAt(map1,Ordinat(cursorLocation),Absis(cursorLocation)) = createWahanaByID(buildingDatabase,tempID+19);
                        money -= buildCost;
                        actionCount++;
                        puts("Wahana telah dibangun!");
                    }
                    else
                        puts("Maaf uang tidak cukup");
                }
                else
                    puts("ID Wahana tidak dapat ditemukan");
                delay(300);
                forceDraw();
                unicodeDraw(1);
            }
            else {
                setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
                puts("Lokasi terpilih tidak dapat dibangun");
            }
        }
        // else if (stringCompare("upgrade",CurrentInput))
        //
        else if (stringCompare("buy",CurrentInput)) {
            printMaterialList();
            wordInput(); // WARNING : Material ID START FROM 10
            int tempID, buyQuantity;
            sscanf(CurrentInput,"%d",&tempID);
            if (searchMaterialByID(materialDatabase,tempID+9)) {
                setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+2);
                puts("Masukkan jumlah yang akan dibeli");
                printf(">> ");
                wordInput();
                sscanf(CurrentInput,"%d",&buyQuantity);
                setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+4);
                int buyCost = buyQuantity * getHargaMaterialByID(materialDatabase,tempID+9);
                if (money >= buyCost) {
                    actionTuple buyLog = { 3,tempID+9,-1,-1,buyQuantity };
                    Push(&actionStack,buyLog);
                    setCountMaterialByID(materialDatabase,tempID+9,buyQuantity+getCountMaterialByID(materialDatabase,tempID+9));
                    currentTime = NextNMenit(currentTime,BUY_TIME); // Buy time
                    money -= buyCost;
                    actionCount++;
                    puts("Material telah dibeli!");
                }
                else
                    puts("Maaf uang tidak cukup");
            }
            else
                puts("ID Material tidak dapat ditemukan");
            delay(300);
            forceDraw();
            unicodeDraw(1);
        }

        else if (stringCompare("undo",CurrentInput)) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            if (!IsEmpty(actionStack)) {
                actionTuple lastAction;
                Pop(&actionStack,&lastAction);
                actionCount--;
                switch (lastAction.actID) {
                    case 1:
                        currentTime = NextNMenit(currentTime,1440-BUILD_TIME);
                        money += lastAction.actIdentifier;
                        destroyWahana(buildingAt(map1,lastAction.eventPosX,lastAction.eventPosY));
                        buildingAt(map1,lastAction.eventPosX,lastAction.eventPosY) = NULL;
                        entityAt(map1,lastAction.eventPosX,lastAction.eventPosY) = 0;
                        occupiedAt(map1,lastAction.eventPosX,lastAction.eventPosY) = false;
                        puts("Wahana telah dibakar");
                        break;
                    case 2:
                        break;
                    case 3:
                        currentTime = NextNMenit(currentTime,1440-BUY_TIME);
                        money += lastAction.actIdentifier * getHargaMaterialByID(materialDatabase,lastAction.entityID);
                        setCountMaterialByID(materialDatabase,lastAction.entityID,getCountMaterialByID(materialDatabase,lastAction.entityID)-lastAction.actIdentifier);
                        puts("Pembelian telah direfund");
                        break;
                }
            }
            else
                puts("Tidak ada aksi yang dapat diundo");
        }


        else if (stringCompare("main",CurrentInput))
            break;
        else if (stringCompare("dbg",CurrentInput)) // DEBUG
            currentTime = NextNMenit(currentTime,5);
        else if (CurrentInput[0] == 'w' || CurrentInput[0] == 'a' || CurrentInput[0] == 's' || CurrentInput[0] == 'd') {
            // ADD Colision detection
            switch (CurrentInput[0]) {
                case 'w':
                    if (1 < Ordinat(cursorLocation))
                        Geser(&cursorLocation,0,-1);
                    break;
                case 'a':
                    if (1 < Absis(cursorLocation))
                        Geser(&cursorLocation,-1,0);
                    break;
                case 's':
                    if (Ordinat(cursorLocation) < MAP_SIZE_Y - 2)
                        Geser(&cursorLocation,0,1);
                    break;
                case 'd':
                    if (Absis(cursorLocation) < MAP_SIZE_X - 2)
                        Geser(&cursorLocation,1,0);
                    break;
            }
        }
    }
    // forceDraw();

}

void playDay() {
    frameSet(2);
    unicodeDraw(2);
    draw();
    // LOOP

    currentDay++;
}





// ----- Draw function set -----
void printBuildList() {
    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+2);
    // TODO : Puts build title
    puts(BUILD_LIST_1);
    puts(BUILD_LIST_2);
    puts(BUILD_LIST_3);
    for (int i = 0 ; i < buildingCount ; i++) // TODO : Print everything
        printf(BUILD_LIST_4, buildingDatabase[i].ID-19, buildingDatabase[i].nama, buildingDatabase[i].harga, buildingDatabase[i].durasi, buildingDatabase[i].kapasitas, buildingDatabase[i].deskripsi);
    puts(BUILD_LIST_5);
    puts("Masukkan ID yang ingin dibangun :");
    printf(">> ");
}

void printMaterialList() {
    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+2);
    // TODO : Puts build title
    puts(MATERIAL_LIST_1);
    puts(MATERIAL_LIST_2);
    puts(MATERIAL_LIST_3);
    for (int i = 0 ; i < materialCount ; i++) // TODO : Print everything
        printf(MATERIAL_LIST_4, materialDatabase[i].ID-9, materialDatabase[i].nama, materialDatabase[i].harga, materialDatabase[i].material_count);
    puts(MATERIAL_LIST_5);
    puts("Masukkan ID yang ingin dibeli :");
    printf(">> ");
}


void frameSet(int tp) { // TODO : Possible merge with other frame function
    // 0 Initialization
    // 1 Preparation
    // 2 Play

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


    char *infoBlock[9], endTime[5];
    if (tp == 1 || tp == 0) {
        infoBlock[4] = "Opening time   | ";
        infoBlock[6] = "     --------------- Action -----------------     ";
        char* actionBlock[3];
        actionBlock[0] = "Action count   | ";
        actionBlock[1] = "Time required  | ";
        actionBlock[2] = "Gold required  | ";
        for (int i = 0 ; i < 3 ; i++)
            for (int j = 0 ; j < INFO_BLOCK_SIZE ; j++)
                infoframe[7+i][j] = actionBlock[i][j];
        sprintf(endTime,"%d",Hour(cPlayTime));
        if (Hour(cPlayTime) < 10) {
            endTime[1] = endTime[0];
            endTime[0] = '0';
        }
    }
    else if (tp == 2) {
        infoBlock[4] = "Closing time   | ";
        infoBlock[6] = "     ---------------- Queue -----------------     ";
        sprintf(endTime,"%d",Hour(cPrepTime));
    }
    endTime[2] = ':';
    endTime[3] = endTime[4] = '0';

    infoBlock[0] = "Name           | ";
    infoBlock[1] = "Money          | ";
    infoBlock[2] = "Day            | ";
    infoBlock[3] = "Current time   | ";
    infoBlock[5] = "Time remaining | ";
    infoBlock[7] = "     ----------------------------------------     ";
    infoBlock[8] = "           ----- Broken Building -----            ";
    for (int i = 0 ; i < 6 ; i++)
        for (int j = 0 ; j < INFO_BLOCK_SIZE ; j++)
            infoframe[i][j] = infoBlock[i][j];

    for (int i = 0 ; i < 5 ; i++)
        infoframe[4][INFO_BLOCK_SIZE+i+1] = endTime[i]; // FIXME : ??


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

    char commandPrompt[] = "Masukkan perintah :                     ";
    for (int i = 0 ; i < 40 ; i++)
        nframe[MAP_OFFSET_Y+MAP_SIZE_Y-2][MAP_OFFSET_X+MAP_SIZE_X+5+i] = commandPrompt[i]; // DEBUG

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
        case 1:
            setCursorPosition(INFO_OFFSET_X-3,INFO_OFFSET_Y-4);
            puts(PREP_DAY_TITLE_1);
            setCursorPosition(INFO_OFFSET_X-3,INFO_OFFSET_Y-3);
            puts(PREP_DAY_TITLE_2);
            break;
        case 2:

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
