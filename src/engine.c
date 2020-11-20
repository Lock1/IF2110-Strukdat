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

matrix map[4];
POINT cursorLocation;
POINT playerLocation;
char username[STRING_LENGTH] = "";
long int actionTime = 0;
int money = START_MONEY;
int currentDay = 1;
int buildingCount = 0;
int materialCount = 0;
JAM currentTime;
Stack actionStack;
int actionCount = 0;
int actionGoldSum = 0;
int currentMap = 0;
char *colorScheme[3] = {COLOR_RESET,COLOR_BLACK,COLOR_WHITE};
int currentColorScheme = 1;

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

boolean integerInput(int *store) {
    while (true) {
        printf(">> ");
        wordInput();
        if (sscanf(CurrentInput,"%d",store))
            return true;
        else if (stringCompare("cancel",CurrentInput))
            return false;
        else
            puts("Masukkan input angka");
    }
}



// ----- Load function -----
void loadMap() {
    // TODO : Load actual map.txt
    for (int i = 0 ; i < 4 ; i++)
        makeMatrix(MAP_SIZE_X,MAP_SIZE_Y,&map[i]);
    for (int a = 0 ; a < 4 ; a++) {
        for (int i = 0 ; i < MAP_SIZE_X ; i++) {
            for (int j = 0 ; j < MAP_SIZE_Y ; j++) {
                if (i == 0 || i == MAP_SIZE_X-1 || j == 0 || j == MAP_SIZE_Y-1) {
                    occupiedAt(map[a],j,i) = true;
                    entityAt(map[a],j,i) = 2;
                }
                else {
                    occupiedAt(map[a],j,i) = false;
                    entityAt(map[a],j,i) = 0;
                }
                buildingAt(map[a],j,i) = NULL;
            }
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
    // Frame wipe
    for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
            infoframe[1][INFO_BLOCK_SIZE+i] = ' '; // Money
    if (tp == 0 || tp == 1)
        for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
                infoframe[7][INFO_BLOCK_SIZE+i] = infoframe[8][INFO_BLOCK_SIZE+i] = infoframe[9][INFO_BLOCK_SIZE+i] = ' '; // Action

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
        targetTime = MenitToJAM(Durasi(currentTime,cPlayTime)); // TODO : Why??
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

    // Window for queue and action
    if (tp == 0 || tp == 1) {
        char actionString[INFO_SIZE_X - INFO_BLOCK_SIZE];
        // Action count
        sprintf(actionString,"%d",actionCount);
        for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
            if (actionString[i] == '\0')
                break;
            else
                infoframe[7][INFO_BLOCK_SIZE+i+1] = actionString[i];
        // Time required
        char actTime[STRING_LENGTH];
        JAM actionTimeRequired = MenitToJAM(actionTime);
        // Hour Handler
        sprintf(tempTime,"%d",Hour(actionTimeRequired));
        if (Hour(actionTimeRequired) < 10) {
            actTime[0] = '0';
            actTime[1] = tempTime[0];
        }
        else {
            actTime[0] = tempTime[0];
            actTime[1] = tempTime[1];
        }
        // Separator
        actTime[2] = ':';
        // Minute Handler
        sprintf(tempTime,"%d",Minute(actionTimeRequired));
        if (Minute(actionTimeRequired) < 10) {
            actTime[3] = '0';
            actTime[4] = tempTime[0];
        }
        else {
            actTime[3] = tempTime[0];
            actTime[4] = tempTime[1];
        }
        // Copying and null terminator
        actTime[5] = '\0';
        for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
            if (actTime[i] == '\0')
                break;
            else
                infoframe[8][INFO_BLOCK_SIZE+i+1] = actTime[i];

        // Gold required
        sprintf(actionString,"%d",actionGoldSum);
        for (int i = 0 ; i < INFO_SIZE_X - INFO_BLOCK_SIZE ; i++)
            if (actionString[i] == '\0')
                break;
            else
                infoframe[9][INFO_BLOCK_SIZE+i+1] = actionString[i];



    }

    // Moving info frame to next frame buffer
    for (int i = 0 ; i < INFO_SIZE_Y ; i++)
        for (int j = 0 ; j < INFO_SIZE_X ; j++)
            nframe[INFO_OFFSET_Y+i][INFO_OFFSET_X+j] = infoframe[i][j];
}

void mapUpdate(int tp) {
    // DEBUG
    for (int i = 0 ; i < MAP_SIZE_Y ; i++)
        for (int j = 0 ; j < MAP_SIZE_X ; j++)
            switch (entityAt(map[currentMap],i,j)) {
                case 0:
                    mapframe[i][j] = '.'; // Nothing
                    break;
                case 1:
                    mapframe[i][j] = '@'; // Player
                    break;
                case 2:
                    mapframe[i][j] = '#'; // Wall
                    break;
                default:
                    if (entityAt(map[currentMap],i,j) > 19)
                        mapframe[i][j] = buildingAt(map[currentMap],i,j)->gambar;
                    break;
            }
    // Draw cursor only on preparation phase
    if (tp == 1)
        mapframe[Ordinat(cursorLocation)][Absis(cursorLocation)] = '*';

     // TODO : Let unique UNICODE char print as '*' at background
    for (int i = 0 ; i < MAP_SIZE_Y ; i++)
        for (int j = 0 ; j < MAP_SIZE_X ; j++)
            nframe[MAP_OFFSET_Y+i][MAP_OFFSET_X+j] = mapframe[i][j];
}





// ----- Game function -----
boolean startGame() {
    while (true) {
        setCursorPosition(0,0);
        if (currentColorScheme != 1)
            puts(colorScheme[1]);
        system(CLSCRN);
        puts(START_MENU_ASCII_ART);
        if (currentColorScheme != 1)
            puts(colorScheme[currentColorScheme]);

        puts("1. New Game");
        // puts("2. Continue"); // TODO : Bonus
        // puts("3. Load game");
        puts("2. Color settings");
        puts("3. Quit");

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
            occupiedAt(map[currentMap],PLAYER_START_X,PLAYER_START_Y) = true;
            entityAt(map[currentMap],PLAYER_START_X,PLAYER_START_Y) = 1;

            return true;
        }
        else if (stringCompare("color", CurrentInput) || CurrentInput[0] == '2') {
            colorSchemeChange();
            drawLoading(30);
            system(CLSCRN);
        }
        else if (stringCompare("quit", CurrentInput) || CurrentInput[0] == '3')
            return false;
    }
    return false;
}

void endGame() {
    puts(colorScheme[0]);
    puts(colorScheme[1]);
    system(CLSCRN);
    puts(QUIT_SCREEN_1);
    puts(QUIT_SCREEN_2);
    exit(0);
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
        // Set cursor pos for repeated input, which can cause weird overwrite
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);

        // If input too long, force draw everything
        if (LengthInput > 15) {
            forceDraw();
            unicodeDraw(1);
        }

        // Input check
        if (stringCompare("build",CurrentInput)) { // TODO : Add double pointer to store build result in play phase
            boolean isAreaBuildable = !occupiedAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation));
            if (isAreaBuildable) {
                printBuildList();// WARNING : BUILDING ID START FROM 20
                int tempID;
                setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+2);
                if (integerInput(&tempID)) {
                    if (searchWahanaByID(buildingDatabase,tempID+19)) {
                        int buildCost = getHargaWahanaByID(buildingDatabase,tempID+19);
                        if (money >= buildCost) {
                            actionTuple buildLog = { 1,tempID+19,Ordinat(cursorLocation),Absis(cursorLocation),buildCost };
                            Push(&actionStack,buildLog);
                            currentTime = NextNMenit(currentTime,BUILD_TIME); // Build time
                            occupiedAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) = true;
                            entityAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) = tempID+19;
                            buildingAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) = createWahanaByID(buildingDatabase,tempID+19);
                            money -= buildCost;
                            actionGoldSum += buildCost;
                            actionCount++;
                            actionTime += BUILD_TIME;
                            puts("Wahana telah dibangun!");
                        }
                        else
                            puts("Maaf uang tidak cukup");
                    }
                    else
                        puts("ID Wahana tidak dapat ditemukan");
                }
                else
                    puts("Pembangunan dibatalkan");
                drawLoading(40);
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
            printMaterialList(); // WARNING : Material ID START FROM 10
            int tempID, buyQuantity;
            if (integerInput(&tempID)) {
                if (searchMaterialByID(materialDatabase,tempID+9)) {
                    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+2);
                    puts("Masukkan jumlah yang akan dibeli");
                    if (integerInput(&buyQuantity)) {
                        setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+4);
                        int buyCost = buyQuantity * getHargaMaterialByID(materialDatabase,tempID+9);
                        if (money >= buyCost) {
                            actionTuple buyLog = { 3,tempID+9,-1,-1,buyQuantity };
                            Push(&actionStack,buyLog);
                            setCountMaterialByID(materialDatabase,tempID+9,buyQuantity+getCountMaterialByID(materialDatabase,tempID+9));
                            currentTime = NextNMenit(currentTime,BUY_TIME); // Buy time
                            money -= buyCost;
                            actionGoldSum += buyCost;
                            actionCount++;
                            actionTime += BUY_TIME;
                            puts("Material telah dibeli!");
                        }
                        else
                        puts("Maaf uang tidak cukup");
                    }
                    else
                    puts("Pembelian dibatalkan");
                }
                else
                puts("ID Material tidak dapat ditemukan");
            }
            else
                puts("Pembelian dibatalkan");
            drawLoading(40);
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
                        actionGoldSum -= lastAction.actIdentifier;
                        actionTime -= BUILD_TIME;
                        destroyWahana(buildingAt(map[currentMap],lastAction.eventPosX,lastAction.eventPosY));
                        buildingAt(map[currentMap],lastAction.eventPosX,lastAction.eventPosY) = NULL;
                        entityAt(map[currentMap],lastAction.eventPosX,lastAction.eventPosY) = 0;
                        occupiedAt(map[currentMap],lastAction.eventPosX,lastAction.eventPosY) = false;
                        puts("Wahana telah dibakar");
                        break;
                    case 2:
                        break;
                    case 3:
                        currentTime = NextNMenit(currentTime,1440-BUY_TIME);
                        money += lastAction.actIdentifier * getHargaMaterialByID(materialDatabase,lastAction.entityID);
                        actionGoldSum -= lastAction.actIdentifier * getHargaMaterialByID(materialDatabase,lastAction.entityID);
                        actionTime -= BUY_TIME;
                        setCountMaterialByID(materialDatabase,lastAction.entityID,getCountMaterialByID(materialDatabase,lastAction.entityID)-lastAction.actIdentifier);
                        puts("Pembelian telah direfund");
                        break;
                }
            }
            else
                puts("Tidak ada aksi yang dapat diundo");
        }
        else if (stringCompare("main",CurrentInput)) // TODO
            break;
        else if (stringCompare("color",CurrentInput)) {
            colorSchemeChange();
            drawLoading(30);
            forceDraw();
            unicodeDraw(1);
        }
        else if (stringCompare("legend",CurrentInput)) {
            printLegendList(1);
            puts("Tekan enter untuk melanjutkan");
            wordInput();
            forceDraw();
            unicodeDraw(1);
        }
        else if (stringCompare("quit",CurrentInput)) {
            // TODO ADD ASCII
            system(CLSCRN);
            setCursorPosition(0,0);

            puts("Are you sure? (y/n)");
            wordInput();
            if (CurrentInput[0] == 'y')
                endGame();
            else {
                forceDraw();
                unicodeDraw(1);
            }
        }

        else if (stringCompare(key,CurrentInput)) {
            system(CLSCRN);
            money += 1000;
            setCursorPosition(0,0);
            puts(wait);
            puts(pressf);
            delay(500);
            forceDraw();
            unicodeDraw(1);
        }
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
    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+3);
    puts(BUILD_TITLE);
    puts(BUILD_LIST_1);
    puts(BUILD_LIST_2);
    puts(BUILD_LIST_3);
    for (int i = 0 ; i < buildingCount ; i++) // TODO : Print everything
        printf(BUILD_LIST_4, buildingDatabase[i].ID-19, buildingDatabase[i].nama, buildingDatabase[i].harga, buildingDatabase[i].durasi, buildingDatabase[i].kapasitas, buildingDatabase[i].deskripsi);
    puts(BUILD_LIST_5);
    puts("Masukkan ID yang ingin dibangun :");
}

void printMaterialList() {
    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+3);
    puts(MATERIAL_TITLE);
    puts(MATERIAL_LIST_1);
    puts(MATERIAL_LIST_2);
    puts(MATERIAL_LIST_3);
    for (int i = 0 ; i < materialCount ; i++) // TODO : Print everything
        printf(MATERIAL_LIST_4, materialDatabase[i].ID-9, materialDatabase[i].nama, materialDatabase[i].harga, materialDatabase[i].material_count);
    puts(MATERIAL_LIST_5);
    puts("Masukkan ID yang ingin dibeli :");
}

void printLegendList(int tp) {
    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+3);
    puts(LEGEND_TITLE);
    puts(LEGEND_LIST_1);
    puts(LEGEND_LIST_2);
    puts(LEGEND_LIST_3);
    if (tp == 0 || tp == 1)
        printf(LEGEND_LIST_4,'*', "Kursor");
    printf(LEGEND_LIST_4,'.', "Kosong");
    printf(LEGEND_LIST_4,'#', "Dinding");
    // TODO other internal reserved ID

    // Scan for current map
    boolean *isAlreadyPrinted = (boolean *) malloc(buildingCount*sizeof(boolean));
    for (int i = 0 ; i < buildingCount ; i++)
        isAlreadyPrinted[i] = false;
    for (int i = 0 ; i < MAP_SIZE_Y ; i++)
        for (int j = 0 ; j < MAP_SIZE_X ; j++)
            switch (entityAt(map[currentMap],i,j)) {
                case 1:
                    printf(LEGEND_LIST_4,'@', "Pemain");
                    break;
                default:
                    if ((entityAt(map[currentMap],i,j) > 19) && !isAlreadyPrinted[entityAt(map[currentMap],i,j)-19]) {
                        printf(LEGEND_LIST_4,buildingAt(map[currentMap],i,j)->gambar,buildingAt(map[currentMap],i,j)->nama);
                        isAlreadyPrinted[entityAt(map[currentMap],i,j)-19] = true;
                    }
                    break;
            }
    free(isAlreadyPrinted); // TODO cleanup not here

    puts(LEGEND_LIST_5);
}

void colorSchemeChange() {
    system(CLSCRN);
    setCursorPosition(0,0);
    puts("Color scheme :");
    puts("1. Black");
    puts("2. White");
    printf(">> ");
    wordInput();
    if (stringCompare("black",CurrentInput) || CurrentInput[0] == '1') {
        puts("Processing ...");
        puts(colorScheme[1]);
        currentColorScheme = 1;
    }
    else if (stringCompare("white",CurrentInput) || CurrentInput[0] == '2') {
        puts("Processing ...");
        puts(colorScheme[2]);
        currentColorScheme = 2;
    }
    else
        puts("Masukkan tidak diketahui");
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

void drawLoading(int fdelay) {
    for (int bar = 0; bar < LOADING_LENGTH ; bar++) {
        printf("\033[1000D");
        fflush(stdout);
        printf(LOADING_OPEN_BRACKET);
        for (int i = 0; i < bar ; i++)
            printf(LOADING_PROGRESS);
        for (int i = bar; i < LOADING_LENGTH ; i++)
            printf(LOADING_NOTHING);
        printf("\033[1000D");
        fflush(stdout);
        printf("\033[20C"); // Have to set for loading length
        fflush(stdout);
        printf(LOADING_CLOSE_BRACKET);
        printf(" ");
        switch (bar%3) {
            case 0:
                putchar('-');
                break;
            case 1:
                putchar('\\');
                break;
            case 2:
                putchar('/');
                break;
        }
        puts(" ");
        delay(fdelay);
        printf("\033[1A");
        fflush(stdout);
    }
    printf("\033[1B");
    fflush(stdout);
}

void unicodeDraw(int tp) {
    // Map UNICODE overwrite
    setCursorPosition(0,0);
    puts(TOP_BORDER);
    setCursorPosition(0,RES_Y-1);
    puts(BOTTOM_BORDER);
    for (int i = 1 ; i < RES_Y-1 ; i++) {
        setCursorPosition(0,i);
        puts("\u2503");
        setCursorPosition(RES_X+3,i);
        puts("\u2503");
    }
    setCursorPosition(3,1);
    puts(MAP_UNICODE);
    for (int i = 2 ; i < MAP_SIZE_Y+2 ; i++) {
        setCursorPosition(3,i);
        puts(MAP_VERTICAL_BORDER);
        setCursorPosition(MAP_SIZE_X+4,i);
        puts(MAP_VERTICAL_BORDER);
    }
    setCursorPosition(3,RES_Y-2);
    puts(MAP_BOTTOM_UNICODE);

    // Information UNICODE overwrite
    setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y-1);
    puts(INFO_UNICODE);

    for (int i = 0 ; i < 12 ; i++) {
        if (i == 6)
            continue;
        setCursorPosition(INFO_OFFSET_X+15,INFO_OFFSET_Y+i);
        puts(INFO_SEPARATOR);
    }
    for (int i = 0 ; i < INFO_SIZE_Y ; i++) {
        if (i%6 || !i) {
            setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+i);
            puts(INFO_VERTICAL_BORDER);
            setCursorPosition(INFO_OFFSET_X+INFO_SIZE_X,INFO_OFFSET_Y+i);
            puts(INFO_VERTICAL_BORDER);
        }
        else {
            setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+i);
            puts(INFO_VERTICAL_DASH);
            setCursorPosition(INFO_OFFSET_X+INFO_SIZE_X,INFO_OFFSET_Y+i);
            puts(INFO_VERTICAL_DASH);
        }
    }
    setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+12);
    puts(INFO_WINDOW_SEP);
    setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+13);
    puts(INFO_BROKEN_BUILDING);
    setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+INFO_SIZE_Y);
    puts(INFO_BOTTOM_UNICODE);

    // TODO : Add play phase print
    switch (tp) {
        case 0:
        case 1:
            setCursorPosition(INFO_OFFSET_X-3,INFO_OFFSET_Y-4);
            puts(PREP_DAY_TITLE_1);
            setCursorPosition(INFO_OFFSET_X-3,INFO_OFFSET_Y-3);
            puts(PREP_DAY_TITLE_2);
            setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+6);
            puts(INFO_PREP_WINDOW);

            break;
        case 2:
            setCursorPosition(INFO_OFFSET_X+10,INFO_OFFSET_Y-4);
            puts(PLAY_DAY_TITLE_1);
            setCursorPosition(INFO_OFFSET_X+10,INFO_OFFSET_Y-3);
            puts(PLAY_DAY_TITLE_2);
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
