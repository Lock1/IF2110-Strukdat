/* 13519214
----- Self note -----
Useful Unicode Char for map
\u2588 -> Solid block
Check box-drawing character in wikipedia for others

\33[ <ANSI Escape codes>
Check ANSI Escape codes for more details

Internal reference in engine.c
Preparation phase -> Prep
Main phase -> Play
Wahana -> Building

// FIXME : Consistency of coordinate space
// TODO : Massive function call refactor
// TODO : Unicode - ASCII Settings
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
int currentBuildingCount = 0;
int materialCount = 0;
int upgradeCount = 0;
JAM currentTime;
Stack actionStack;
int actionCount = 0;
int actionGoldSum = 0;
int currentState = 0;
int currentMap = 0;
int playerMapLocation = 0;
char *colorScheme[3] = {COLOR_RESET,COLOR_BLACK,COLOR_WHITE};
int currentColorScheme = 1;

Wahana* buildingDatabase;
Material* materialDatabase;
BinTree* upgradeDatabase;
Wahana** currentBuildingDatabase;
int currentBuildingCapacity[MAX_SERVE];
POINT* buildingLocationDatabase;
addrGraph mapGraph;
PrioQueueChar playQueue;
queueElmtType currentServe[MAX_SERVE];
int currentServeDuration[MAX_SERVE];
int currentServeBuildingIndex[MAX_SERVE];
boolean currentServeDone[MAX_SERVE];
int lastServeIndex = 0;

// -------------------------------------------------------


// ---------------- Function Definition =-----------------

// ----- Other function -----
// Theres function in Windows that allow set cursor pos
// Anyway UNIX implementation pretty short
void setCursorPosition(int XPos, int YPos) {
    printf("\033[%d;%dH",YPos+1,XPos+1);
}

void stringCopy(char src[STRING_LENGTH], char dst[STRING_LENGTH]) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i]; // FIXME : maybe null terminator
        i++;
    }
    dst[i] = '\0';
}

boolean stringCompare(char st1[STRING_LENGTH], char st2[STRING_LENGTH]) {
    for (int i = 0 ; st1[i] != '\0' ; i++)
        if (st1[i] != st2[i])
            return false; // FIXME : Both Constant strings
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
    POINT* initialLocation = ReadFromMap();

    // Initial map graph
    mapGraph = createAGraph(4);
    addEdge(mapGraph, 0, 1);
    addEdge(mapGraph, 0, 2);
    addEdge(mapGraph, 1, 2);
    addEdge(mapGraph, 1, 3);
    addEdge(mapGraph, 2, 3);
    addEdge(mapGraph, 3, 0);

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

    playerLocation = MakePOINT(Ordinat(initialLocation[0]), Absis(initialLocation[0]));
    entityAt(map[0],Absis(initialLocation[0]),Ordinat(initialLocation[0])) = 1; // Player location
    occupiedAt(map[0],Absis(initialLocation[0]),Ordinat(initialLocation[0])) = true;
    entityAt(map[0],Absis(initialLocation[1]),Ordinat(initialLocation[1])) = 7; // Office location
    occupiedAt(map[0],Absis(initialLocation[1]),Ordinat(initialLocation[1])) = true;
    entityAt(map[0],Absis(initialLocation[2]),Ordinat(initialLocation[2])) = 8; // Queue location
    occupiedAt(map[0],Absis(initialLocation[2]),Ordinat(initialLocation[2])) = true;
    free(initialLocation); // NOTE : Not here
}

void loadDatabase() {
    materialCount = ReadFromBahan(&materialDatabase);
    buildingCount = ReadFromWahana(&buildingDatabase,materialCount);
    upgradeCount = MakePohonUpgrade(&upgradeDatabase,buildingCount); // TODO : Fix
    currentBuildingDatabase = (Wahana**) malloc(MAX_WAHANA*sizeof(Wahana*));
    buildingLocationDatabase = (POINT*) malloc(MAX_WAHANA*sizeof(POINT));
    MakeEmptyQueue(&playQueue,MAX_QUEUE);
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

    else if (tp == 2) {
        // Wipe old record
        for (int i = 0 ; i < 5 ; i++)
            for (int j = 0 ; j < INFO_SIZE_X ; j++)
                infoframe[7+i][j] = ' ';
        // Write queue
        int maxPrint;
        if (NBElmtQueue(playQueue) < 6)
            maxPrint = NBElmtQueue(playQueue);
        else
            maxPrint = 5;
        for (int i = 0 ; i < maxPrint ; i++) { // Only able print 5 queue
            queueElmtType customer = QueueElmt(playQueue, (Head(playQueue) + QueueMaxEl(playQueue) + i) % QueueMaxEl(playQueue));
            char queueString[STRING_LENGTH];
            for (int p = 0 ; p < STRING_LENGTH ; p++)
                queueString[p] = ' ';
            int k = 0;
            while (k < 22 && (*currentBuildingDatabase[customer.info[0]]).nama[k] != '\0') {
                if (!customer.isServed[0])
                    queueString[k] = (*currentBuildingDatabase[customer.info[0]]).nama[k];
                else
                    queueString[k] = ' ';
                k++;
            }
            k = 0;
            while (k < 22 && (*currentBuildingDatabase[customer.info[1]]).nama[k] != '\0') {
                if (!customer.isServed[1])
                    queueString[20+k] = (*currentBuildingDatabase[customer.info[1]]).nama[k];
                else
                    queueString[20+k] = ' ';
                k++;
            }

            char happyValue[STRING_LENGTH];
            // char *happyValue = "aaaabbbb";
            sprintf(happyValue,"Sabar : %d", customer.happiness);
            for (int j = 0 ; happyValue[j] != '\0' ; j++)
                queueString[40+j] = happyValue[j];
            queueString[49] = '\0';
            for (int j = 0 ; j < INFO_SIZE_X && queueString[j] != '\0'; j++)
                infoframe[7+i][j] = queueString[j];
        }
    }


    // Broken building check
    int brokenBuildingCount = 0;
    // Wipe old record
    for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < INFO_SIZE_X ; j++)
            infoframe[14+i][j] = ' ';
    }
    for (int i = 0 ; i < currentBuildingCount ; i++) {
        if (!(*currentBuildingDatabase[i]).statusWahana && brokenBuildingCount < 3) {
            for (int j = 0 ; j < INFO_SIZE_X/2 && (*currentBuildingDatabase[i]).nama[j] != '\0'; j++)
                infoframe[14+brokenBuildingCount][j] = (*currentBuildingDatabase[i]).nama[j];
            char brokenLocation[STRING_LENGTH];
            sprintf(brokenLocation,"(%d,%d)",Absis(buildingLocationDatabase[i]),Ordinat(buildingLocationDatabase[i]));
            for (int j = 0 ; j < INFO_SIZE_X/2 && brokenLocation[j] != '\0'; j++)
                infoframe[14+brokenBuildingCount][INFO_SIZE_X/2+j] = brokenLocation[j];
            brokenBuildingCount++;
        }
    }


    // Moving info frame to next frame buffer
    for (int i = 0 ; i < INFO_SIZE_Y ; i++)
        for (int j = 0 ; j < INFO_SIZE_X ; j++)
            nframe[INFO_OFFSET_Y+i][INFO_OFFSET_X+j] = infoframe[i][j];
}

void mapUpdate(int tp) {
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
                case 7:
                    mapframe[i][j] = 'o'; // Office
                    break;
                case 8:
                    mapframe[i][j] = 'a'; // Queue
                    break;
                default:
                    if (entityAt(map[currentMap],i,j) > 19) {
                        if (!LinIsEmpty((*buildingAt(map[currentMap],i,j)).upgrade)) {
                            int currentUpgradeID = Info(First((*buildingAt(map[currentMap],i,j)).upgrade));
                            mapframe[i][j] = getCharByID(buildingDatabase, currentUpgradeID);
                        }
                        else
                            mapframe[i][j] = buildingAt(map[currentMap],i,j)->gambar;

                    }
                    break;
            }

    // Draw cursor only on preparation phase
    if (tp == 1) {
        mapframe[Ordinat(cursorLocation)][Absis(cursorLocation)] = 'x';
        // setCursorPosition(Absis(cursorLocation)+MAP_OFFSET_X,Ordinat(cursorLocation)+MAP_OFFSET_Y);
        // puts("\u2588");
    }

    else if (tp == 2) {
        mapframe[Ordinat(playerLocation)][Absis(playerLocation)] = '@';
    }

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
            return true;
        }
        else if (stringCompare("color", CurrentInput) || CurrentInput[0] == '2') {
            colorSchemeChange(30);
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

// -- Action function --
void buildNewBuilding(void) {
    // TODO : Add double pointer to store build result in play phase
    boolean isAreaBuildable = !occupiedAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation));
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    if (isAreaBuildable) {
        if ((Durasi(currentTime,cPlayTime)%1440 - BUILD_TIME) >= 0) {
            printBuildList();// WARNING : BUILDING ID START FROM 20
            int tempID;
            setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+2);
            if (integerInput(&tempID)) {
                if ((tempID < 120) && searchWahanaByID(buildingDatabase,tempID+19)) {
                    int buildCost = getHargaWahanaByID(buildingDatabase,tempID+19);
                    if (money >= buildCost) {
                        boolean isMaterialEnough = true;
                        Wahana selectedBuilding = buildingDatabase[getIndexByID(buildingDatabase,tempID + 19)];
                        // Warn : Direct access
                        for (int i = 0 ; i < materialCount ; i++)
                            if (selectedBuilding.materialArray[i] > materialDatabase[i].material_count)
                                isMaterialEnough = false;
                        if (isMaterialEnough) {
                            for (int i = 0 ; i < materialCount ; i++)
                                materialDatabase[i].material_count -= selectedBuilding.materialArray[i];
                            actionTuple buildLog = { 1,tempID+19,Ordinat(cursorLocation),Absis(cursorLocation),buildCost,currentMap };
                            Push(&actionStack,buildLog);
                            currentTime = NextNMenit(currentTime,BUILD_TIME); // Build time
                            occupiedAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) = true;
                            entityAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) = tempID + 19;
                            Wahana* newBuilding = createWahanaByID(buildingDatabase,tempID + 19);
                            buildingAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) = newBuilding;
                            buildingLocationDatabase[currentBuildingCount] = MakePOINT(Absis(cursorLocation),Ordinat(cursorLocation));
                            currentBuildingDatabase[currentBuildingCount] = newBuilding;
                            currentBuildingCount++;
                            money -= buildCost;
                            actionGoldSum += buildCost;
                            actionCount++;
                            actionTime += BUILD_TIME;
                            puts("Wahana telah dibangun!");
                        }
                        else
                            puts("Maaf material tidak cukup");
                    }
                    else
                        puts("Maaf uang tidak cukup");
                }
                else
                    puts("ID Wahana tidak dapat ditemukan");
            }
            else
                puts("Pembangunan dibatalkan");
            drawLoading(20);
            forceDraw();
            unicodeDraw(1);
        }
        else
            puts("Maaf durasi waktu tidak cukup");
    }
    else {
        puts("Lokasi terpilih tidak dapat dibangun");
    }
}

void upgradeBuilding(void) {
    boolean isOccupiedAt = occupiedAt(map[currentMap], Ordinat(cursorLocation), Absis(cursorLocation));
    int entityIDAtCursor = entityAt(map[currentMap], Ordinat(cursorLocation), Absis(cursorLocation));
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    if (isOccupiedAt && 25 >= entityIDAtCursor && entityIDAtCursor >= 20) { // Temp
        if ((Durasi(currentTime,cPlayTime) % 1440 - UPGRADE_TIME) >= 0){
            int originalIndex = getIndexByID(buildingDatabase, entityAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)));
            printUpgradeList(originalIndex);
            int tempID;
            if (integerInput(&tempID)) {
                // WARNING : Upgrade offset
                if ((tempID == Akar(Left(upgradeDatabase[originalIndex])) - 119) || (tempID == Akar(Right(upgradeDatabase[originalIndex]))) - 219) {
                    int upgradeID = entityAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation));
                    if (tempID == 1)
                        upgradeID += 100;
                    else
                        upgradeID += 200;
                    // Change tempID to store original unupgraded building
                    tempID = entityAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation));
                    int upgradeCost = getHargaWahanaByID(buildingDatabase, upgradeID);
                    if (money >= upgradeCost) {
                        boolean isMaterialEnough = true;
                        Wahana selectedBuilding = buildingDatabase[getIndexByID(buildingDatabase,upgradeID)];
                        // Warn : Direct access
                        for (int i = 0 ; i < materialCount ; i++) // TODO : Change building stat
                            if (selectedBuilding.materialArray[i] > materialDatabase[i].material_count)
                                isMaterialEnough = false;
                        if (isMaterialEnough) {
                            for (int i = 0 ; i < materialCount ; i++)
                                materialDatabase[i].material_count -= selectedBuilding.materialArray[i];
                            actionTuple upgradeLog = { 2, upgradeID, Ordinat(cursorLocation), Absis(cursorLocation), tempID, currentMap };
                            Push(&actionStack,upgradeLog);
                            currentTime = NextNMenit(currentTime,UPGRADE_TIME); // Upgrade time
                            entityAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) = upgradeID;
                            InsVLast(&Upgrade(*buildingAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation))),upgradeID);
                            (*buildingAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation))).harga += selectedBuilding.harga;
                            (*buildingAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation))).kapasitas += selectedBuilding.kapasitas;
                            (*buildingAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation))).durasi -= selectedBuilding.durasi;
                            money -= upgradeCost;
                            actionGoldSum += upgradeCost;
                            actionCount++;
                            actionTime += UPGRADE_TIME;
                            puts("Wahana telah diupgrade!");
                        }
                        else
                            puts("Maaf material tidak cukup");
                    }
                    else
                        puts("Maaf uang tidak cukup");
                }
                else
                    puts("ID upgrade tidak ditemukan");
            }
            else
                puts("Upgrade dibatalkan");
            drawLoading(20);
            forceDraw();
            unicodeDraw(1);
        }
        else
            puts("Maaf durasi waktu tidak cukup");
    }
    else
        puts("Tidak ditemukan wahana yang dapat diupgrade");
}

void buyMaterial(void) {
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    if ((Durasi(currentTime,cPlayTime)%1440 - BUY_TIME) >= 0) {
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
                        actionTuple buyLog = { 3,tempID+9,-1,-1,buyQuantity,-1 };
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
        drawLoading(20);
        forceDraw();
        unicodeDraw(1);
    }
    else
        puts("Maaf durasi waktu tidak cukup");
}

int actionUndo() {
    /* Undo table
    | ActID | Action |
    | ----- | ------ |
    | 1     | Build  |
    | 2     | Upgrade|
    | 3     | Buy    |
    | -------------- |
    Return 0 if no undo performed,
    else return corresponding ActID
    */
    if (!IsEmpty(actionStack)) {
        actionTuple lastAction;
        Pop(&actionStack,&lastAction);
        actionCount--;
        switch (lastAction.actID) {
            case 1: {
                Wahana selectedBuilding = buildingDatabase[getIndexByID(buildingDatabase,lastAction.entityID)];
                for (int i = 0 ; i < materialCount ; i++)
                    materialDatabase[i].material_count += selectedBuilding.materialArray[i];
                currentTime = NextNMenit(currentTime,1440-BUILD_TIME);
                currentBuildingCount--;
                money += lastAction.actIdentifier;
                actionGoldSum -= lastAction.actIdentifier;
                actionTime -= BUILD_TIME;
                destroyWahana(buildingAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY));
                buildingAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY) = NULL;
                entityAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY) = 0;
                occupiedAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY) = false;
                return 1;
                break;
            }
            case 2: {
                Wahana upgradedBuilding = buildingDatabase[getIndexByID(buildingDatabase,lastAction.entityID)];
                int upgradeCost = upgradedBuilding.harga;
                int tempTrash;
                for (int i = 0 ; i < materialCount ; i++)
                    materialDatabase[i].material_count += upgradedBuilding.materialArray[i];
                currentTime = NextNMenit(currentTime,1440-UPGRADE_TIME);
                money += upgradeCost;
                actionGoldSum -= upgradeCost;
                actionTime -= UPGRADE_TIME;
                (*buildingAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY)).harga -= upgradedBuilding.harga;
                (*buildingAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY)).kapasitas -= upgradedBuilding.kapasitas;
                (*buildingAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY)).durasi += upgradedBuilding.durasi;
                entityAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY) = lastAction.actIdentifier;
                DelVLast(&Upgrade(*buildingAt(map[lastAction.actionMap],lastAction.eventPosX,lastAction.eventPosY)),&tempTrash);
                return 2;
                break;
            }
            case 3:
                currentTime = NextNMenit(currentTime,1440-BUY_TIME);
                money += lastAction.actIdentifier * getHargaMaterialByID(materialDatabase,lastAction.entityID);
                actionGoldSum -= lastAction.actIdentifier * getHargaMaterialByID(materialDatabase,lastAction.entityID);
                actionTime -= BUY_TIME;
                setCountMaterialByID(materialDatabase,lastAction.entityID,getCountMaterialByID(materialDatabase,lastAction.entityID)-lastAction.actIdentifier);
                return 3;
                break;
            default:
                return 0;
                break;
        }
    }
    else
        return 0;
}

void getDetails() {
    if (currentBuildingCount > 0) {
        setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+3);
        puts(DETAIL_WAHANA_TITLE);
        puts(DETAIL_WAHANA_LIST_1);
        puts(DETAIL_WAHANA_LIST_2);
        puts(DETAIL_WAHANA_LIST_3);
        for (int i = 0 ; i < currentBuildingCount ; i++) {
            int posX = Absis(buildingLocationDatabase[i]), posY = Ordinat(buildingLocationDatabase[i]);
            if (!LinIsEmpty((*currentBuildingDatabase[i]).upgrade)) {
                int upgradeIndex = getIndexByID(buildingDatabase,Info(First((*currentBuildingDatabase[i]).upgrade)));
                char upgradeName[STRING_LENGTH];
                stringCopy(buildingDatabase[upgradeIndex].nama,upgradeName);
                printf(DETAIL_WAHANA_LIST_4, (*currentBuildingDatabase[i]).ID, (*currentBuildingDatabase[i]).nama, (*currentBuildingDatabase[i]).harga, posX, posY, (*currentBuildingDatabase[i]).durasi, (*currentBuildingDatabase[i]).kapasitas, (*currentBuildingDatabase[i]).deskripsi, upgradeName);
            }
            else
                printf(DETAIL_WAHANA_LIST_4, (*currentBuildingDatabase[i]).ID, (*currentBuildingDatabase[i]).nama, (*currentBuildingDatabase[i]).harga, posX, posY, (*currentBuildingDatabase[i]).durasi, (*currentBuildingDatabase[i]).kapasitas, (*currentBuildingDatabase[i]).deskripsi, "Tidak ada");
            // TODO : Location
            // Upgrade wahana
            // printf("%s\n",(*currentBuildingDatabase[i]).kapasitas);
        }
        puts(DETAIL_WAHANA_LIST_5);
        puts("Tekan enter untuk melanjutkan");
        wordInput();
        forceDraw(2);
        unicodeDraw(2);
    }
    else {
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
        puts("Tidak ada bangunan");
    }
}

void getLaporan() {
    if (currentBuildingCount > 0) {
        setCursorPosition(0,MAP_OFFSET_Y + MAP_SIZE_Y + 3);
        puts(LAPORAN_WAHANA_TITLE);
        puts(LAPORAN_WAHANA_LIST_1);
        puts(LAPORAN_WAHANA_LIST_2);
        puts(LAPORAN_WAHANA_LIST_3);
        for (int i = 0 ; i < currentBuildingCount ; i++)
            printf(LAPORAN_WAHANA_LIST_4, (*currentBuildingDatabase[i]).ID, (*currentBuildingDatabase[i]).nama, (*currentBuildingDatabase[i]).frekuensiTotal, (*currentBuildingDatabase[i]).penghasilanTotal, (*currentBuildingDatabase[i]).frekuensiHari, (*currentBuildingDatabase[i]).penghasilanHari);
        puts(LAPORAN_WAHANA_LIST_5);
        puts("Tekan enter untuk melanjutkan");
        wordInput();
        forceDraw(2);
        unicodeDraw(2);
    }
    else {
        setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X + 5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
        puts("Tidak ada bangunan");
    }
}

void repairBuilding(int posX, int posY) {
    Wahana* selectedBuilding = buildingAt(map[currentMap], posX, posY);
    setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X + 5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    if (!(*selectedBuilding).statusWahana) {
        // Time checking
        boolean isTimeEnough = false;
        if (currentState == 0 && (Durasi(currentTime,cPlayTime)%1440 - REPAIR_TIME) >= 0)
            isTimeEnough = true;
        else if (currentState == 1 && (Durasi(currentTime,cPrepTime)%1440 - REPAIR_TIME) >= 0)
            isTimeEnough = true;

        if (isTimeEnough) {
            printf("Perbaiki %s dengan harga %d? (y/n)", (*selectedBuilding).nama, (*selectedBuilding).harga);
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X + 25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
            wordInput();
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X + 5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            if (CurrentInput[0] == 'y') {
                if (money >= (*selectedBuilding).harga) {
                    (*selectedBuilding).statusWahana = 1;
                    money -= (*selectedBuilding).harga;
                    currentTime = NextNMenit(currentTime,REPAIR_TIME);
                    printf("%s telah diperbaiki!               ", (*selectedBuilding).nama);
                }
                else
                    printf("Uang tidak cukup untuk perbaiki");
            }
            else
                printf("%s tidak diperbaiki                  ", (*selectedBuilding).nama);
            }
        else
            printf("Maaf waktu tidak cukup                 ");
    }
    else
        printf("%s tidak rusak", (*selectedBuilding).nama);
    setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X + 25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    printf("                            ");
}
// DEBUG for checking repair
void destroy(int af) {
    for (int i = 0 ; i < currentBuildingCount ; i++)
        (*currentBuildingDatabase[i]).statusWahana = 0;
    for (int i = 0 ; i < NBElmtQueue(playQueue) ; i++) {
        if (af == 1) {
            *(&(QueueElmt(playQueue,i).isServed[0])) = true;
        }
        else {
            *(&(QueueElmt(playQueue,i).isServed[1])) = true;
        }
    }
    for (int i = 0 ; i < currentBuildingCount ; i++) {
        (*currentBuildingDatabase[i]).frekuensiHari += 1;
        (*currentBuildingDatabase[i]).frekuensiTotal += 3;
        (*currentBuildingDatabase[i]).penghasilanHari += 2;
        (*currentBuildingDatabase[i]).penghasilanTotal += 7;

    }
}

void generateNewCustomer() {
    // TODO : Random seed
    // srand(CurrentInput[1]);
    int rollValue = random() % 100;
    if (NBElmtQueue(playQueue) < 6 && currentBuildingCount > 0 && rollValue < 10) {
        queueElmtType newCustomer;
        // TODO : Temporary using 2 building only
        newCustomer.prio = 10;
        newCustomer.info[0] = random() % (currentBuildingCount);
        newCustomer.info[1] = random() % (currentBuildingCount);
        newCustomer.isServed[0] = false;
        newCustomer.isServed[1] = false;
        newCustomer.happiness = 5;
        Enqueue(&playQueue,newCustomer);
    }
}

void generateCustomer() { // DEBUG
    queueElmtType newCustomer;
    // TODO : Temporary using 2 building only
    newCustomer.prio = 3;
    newCustomer.info[0] = random() % (currentBuildingCount);
    newCustomer.info[1] = random() % (currentBuildingCount);
    newCustomer.isServed[0] = false;
    newCustomer.isServed[1] = false;
    newCustomer.happiness = 3;
    Enqueue(&playQueue,newCustomer);
}

void customerTickCheck() {
    if (NBElmtQueue(playQueue) > 0) {
        int currentIndex = Head(playQueue);
        queueElmtType frontCustomer = QueueElmt(playQueue,currentIndex);
        if ((frontCustomer.isServed[0] && frontCustomer.isServed[1]) || frontCustomer.happiness < 1) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y);
            printf("Pelanggan telah keluar dari queue");
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
            queueElmtType tempTrash;
            Dequeue(&playQueue,&tempTrash);
        }
        else {
            if (15 > (random() % 100))
                *(&(QueueElmt(playQueue,currentIndex).happiness)) = QueueElmt(playQueue,currentIndex).happiness - 1;
        }
        currentIndex = Head(playQueue);
        while (currentIndex != Tail(playQueue)) {
            frontCustomer = QueueElmt(playQueue,currentIndex);
            if ((frontCustomer.isServed[0] && frontCustomer.isServed[1]) || frontCustomer.happiness < 1) {
                queueElmtType tempTrash;
                Dequeue(&playQueue,&tempTrash);
            }
            currentIndex = (currentIndex + 1) % QueueMaxEl(playQueue);
        }
    }
}

void customerPlayingCheck() {
    for (int i = 0 ; i < lastServeIndex ; i++) {
        if (!currentServeDone[i] && currentServeDuration[i] > 0)
            currentServeDuration[i] -= MOVE_TIME; // FIXME : Actually not accurate but whatever
        else if (!currentServeDone[i] && currentServeDuration[i] == 0) {
            boolean rollBreak = 25 > (random() % 100);
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y);
            int moneyGain = (*currentBuildingDatabase[currentServeBuildingIndex[i]]).harga;
            printf("Mendapatkan uang %d!",moneyGain);
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
            *(&currentBuildingCapacity[currentServeBuildingIndex[i]]) = currentBuildingCapacity[currentServeBuildingIndex[i]] + 1;
            currentServeDone[i] = true;
            (*currentBuildingDatabase[currentServeBuildingIndex[i]]).frekuensiHari = (*currentBuildingDatabase[currentServeBuildingIndex[i]]).frekuensiHari + 1;
            (*currentBuildingDatabase[currentServeBuildingIndex[i]]).frekuensiTotal = (*currentBuildingDatabase[currentServeBuildingIndex[i]]).frekuensiTotal + 1;
            (*currentBuildingDatabase[currentServeBuildingIndex[i]]).penghasilanHari = (*currentBuildingDatabase[currentServeBuildingIndex[i]]).penghasilanHari + moneyGain;
            (*currentBuildingDatabase[currentServeBuildingIndex[i]]).penghasilanTotal = (*currentBuildingDatabase[currentServeBuildingIndex[i]]).penghasilanTotal + moneyGain;
            money += (*currentBuildingDatabase[currentServeBuildingIndex[i]]).harga;
            if (rollBreak)
                (*currentBuildingDatabase[currentServeBuildingIndex[i]]).statusWahana = false;
            currentServe[i].prio = 1;
            Enqueue(&playQueue,currentServe[i]);
        }
    }
}

void serveCustomer() {
    queueElmtType servedCustomer;
    if (NBElmtQueue(playQueue) > 0) {
        Wahana firstBuilding = *currentBuildingDatabase[QueueElmt(playQueue,Head(playQueue)).info[0]];
        Wahana secondBuilding = *currentBuildingDatabase[QueueElmt(playQueue,Head(playQueue)).info[1]];
        int firstBuildingIndex = QueueElmt(playQueue,Head(playQueue)).info[0];
        int secondBuildingIndex = QueueElmt(playQueue,Head(playQueue)).info[1];
        int* firstBuildingCapacity = &currentBuildingCapacity[QueueElmt(playQueue,Head(playQueue)).info[0]];
        int* secondBuildingCapacity = &currentBuildingCapacity[QueueElmt(playQueue,Head(playQueue)).info[1]];
        boolean isFirstBuildingDone = QueueElmt(playQueue,Head(playQueue)).isServed[0];
        boolean isSecondBuildingDone = QueueElmt(playQueue,Head(playQueue)).isServed[1];
        boolean isFirstServeFail = true, isSecondServeFail = true;
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y);
        if (!isFirstBuildingDone)  {
            if (firstBuilding.statusWahana) {
                if (*firstBuildingCapacity > 0) {
                    Dequeue(&playQueue,&servedCustomer);
                    printf("Serve wahana %s!",firstBuilding.nama);
                    *firstBuildingCapacity = *firstBuildingCapacity - 1;
                    servedCustomer.isServed[0] = true;
                    currentServe[lastServeIndex] = servedCustomer;
                    currentServeDuration[lastServeIndex] = firstBuilding.durasi;
                    currentServeDone[lastServeIndex] = false;
                    currentServeBuildingIndex[lastServeIndex] = firstBuildingIndex;
                    lastServeIndex++;
                    isFirstServeFail = false;
                }
                else
                    printf("Wahana %s sedang penuh                  ",firstBuilding.nama);
            }
            else
                printf("Wahana %s sedang rusak             ",firstBuilding.nama);
        }
        if (!isSecondBuildingDone && isFirstServeFail) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            if (secondBuilding.statusWahana) {
                if (*secondBuildingCapacity > 0) {
                    Dequeue(&playQueue,&servedCustomer);
                    printf("Serve wahana %s!",secondBuilding.nama);
                    *secondBuildingCapacity = *secondBuildingCapacity - 1;
                    servedCustomer.isServed[1] = true;
                    currentServe[lastServeIndex] = servedCustomer;
                    currentServeDuration[lastServeIndex] = secondBuilding.durasi;
                    currentServeDone[lastServeIndex] = false;
                    currentServeBuildingIndex[lastServeIndex] = secondBuildingIndex;
                    lastServeIndex++;
                    isSecondServeFail = false;
                }
                else
                    printf("Wahana %s sedang penuh              ",secondBuilding.nama);
            }
            else
                printf("Wahana %s sedang rusak             ",secondBuilding.nama);
        }
        if (isFirstServeFail && isSecondServeFail) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y);
            puts("Tidak ada yang dapat diserve                  ");
        }
    }
    else
        puts("Tidak ada antrian                 ");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
}

void playPhaseSetup() {
    for (int i = 0 ; i < currentBuildingCount ; i++) {
        currentBuildingCapacity[i] = (*currentBuildingDatabase[i]).kapasitas;
        (*currentBuildingDatabase[i]).frekuensiHari = 0;
        (*currentBuildingDatabase[i]).penghasilanHari = 0;
    }
}


// -- Movement function --
void moveCursor(POINT* movingObject, char input, boolean collision) {
    // FIXME : Collision in edge of map
    // TODO : Collison interaction
    if (collision) {
        switch (input) {
            case 'w': {
                boolean isTraversable = !occupiedAt(map[currentMap],Ordinat(*movingObject) - 1, Absis(*movingObject));
                if (20 <= entityAt(map[currentMap],Ordinat(*movingObject) - 1, Absis(*movingObject)))
                    buildingCollisionPrompt(Ordinat(*movingObject) - 1, Absis(*movingObject));
                else if (7 == entityAt(map[currentMap],Ordinat(*movingObject) - 1, Absis(*movingObject)))
                    officeCollisionPrompt();
                else if (8 == entityAt(map[currentMap],Ordinat(*movingObject) - 1, Absis(*movingObject)))
                    queueCollisionPrompt();
                else if (1 < Ordinat(*movingObject) && isTraversable) {
                    Geser(movingObject,0,-1);
                    currentTime = NextNMenit(currentTime,MOVE_TIME); // TODO : Time should not tied with collision
                }
                break;
            }
            case 'a': {
                boolean isTraversable = !occupiedAt(map[currentMap],Ordinat(*movingObject), Absis(*movingObject) - 1);
                if (20 <= entityAt(map[currentMap],Ordinat(*movingObject), Absis(*movingObject) - 1))
                    buildingCollisionPrompt(Ordinat(*movingObject), Absis(*movingObject) - 1);
                else if (7 == entityAt(map[currentMap],Ordinat(*movingObject), Absis(*movingObject) - 1))
                    officeCollisionPrompt();
                else if (8 == entityAt(map[currentMap],Ordinat(*movingObject), Absis(*movingObject) - 1))
                    queueCollisionPrompt();
                else if (Absis(*movingObject) > 1 && isTraversable) {
                    Geser(movingObject,-1,0);
                    currentTime = NextNMenit(currentTime,MOVE_TIME); // TODO : Time should not tied with collision
                }
                // TODO : add detail + office here
                break;
            }
            case 's': {
                boolean isTraversable = !occupiedAt(map[currentMap],Ordinat(*movingObject) + 1, Absis(*movingObject));
                if (20 <= entityAt(map[currentMap],Ordinat(*movingObject) + 1, Absis(*movingObject)))
                    buildingCollisionPrompt(Ordinat(*movingObject) + 1, Absis(*movingObject));
                else if (7 ==  entityAt(map[currentMap],Ordinat(*movingObject) + 1, Absis(*movingObject)))
                    officeCollisionPrompt();
                else if (8 ==  entityAt(map[currentMap],Ordinat(*movingObject) + 1, Absis(*movingObject)))
                    queueCollisionPrompt();
                else if (Ordinat(*movingObject) < MAP_SIZE_Y - 2 && isTraversable) {
                    Geser(movingObject,0,1);
                    currentTime = NextNMenit(currentTime,MOVE_TIME); // TODO : Time should not tied with collision
                }
                break;
            }
            case 'd': {
                boolean isTraversable = !occupiedAt(map[currentMap],Ordinat(*movingObject), Absis(*movingObject) + 1);
                if (20 <= entityAt(map[currentMap],Ordinat(*movingObject), Absis(*movingObject) + 1))
                    buildingCollisionPrompt(Ordinat(*movingObject), Absis(*movingObject) + 1);
                else if (7 == entityAt(map[currentMap],Ordinat(*movingObject), Absis(*movingObject) + 1))
                    officeCollisionPrompt();
                else if (8 == entityAt(map[currentMap],Ordinat(*movingObject), Absis(*movingObject) + 1))
                    queueCollisionPrompt();
                else if (Absis(*movingObject) < MAP_SIZE_X - 2 && isTraversable) {
                    Geser(movingObject,1,0);
                    currentTime = NextNMenit(currentTime,MOVE_TIME); // TODO : Time should not tied with collision
                }
                break;
            }
        }
    }

    else {
        switch (input) {
            case 'w':
                if (1 < Ordinat(*movingObject))
                    Geser(movingObject,0,-1);
                break;
            case 'a':
                if (Absis(*movingObject) > 1)
                    Geser(movingObject,-1,0);
                break;
            case 's':
                if (Ordinat(*movingObject) < MAP_SIZE_Y - 2)
                    Geser(movingObject,0,1);
                break;
            case 'd':
                if (Absis(*movingObject) < MAP_SIZE_X - 2)
                    Geser(movingObject,1,0);
                break;
        }
    }
}


void moveMap(POINT* movingObject, char input, int drawMode, boolean collision) {
    switch (currentMap) {
        case 0:
            // Right arrow
            if (Absis(*movingObject) == (MAP_SIZE_X - 2) && input == 'd') {
                if (isGraphConnected(mapGraph,0,1))
                    if ((MAP_SIZE_Y / 2 - 1) <= Ordinat(*movingObject) && Ordinat(*movingObject) <= (MAP_SIZE_Y / 2 + 1)) {
                        currentMap = 1;
                        Geser(movingObject,3-MAP_SIZE_X,0); //-= (MAP_SIZE_X - 3);
                        unicodeDraw(drawMode);
                    }
            }
            // Down arrow
            else if (Ordinat(*movingObject) == (MAP_SIZE_Y - 2) && input == 's') {
                if (isGraphConnected(mapGraph,0,2))
                    if ((MAP_SIZE_X / 2 - 3) <= Absis(*movingObject) && Absis(*movingObject) <= (MAP_SIZE_X / 2 + 1)) {
                        currentMap = 2;
                        Geser(movingObject,0,3-MAP_SIZE_Y);
                        unicodeDraw(drawMode);
                    }
            }
            else
                moveCursor(movingObject,input,collision);
            break;
        case 1:
            // Left arrow
            if (Absis(*movingObject) == 1 && input == 'a') {
                if (isGraphConnected(mapGraph,1,0))
                    if ((MAP_SIZE_Y / 2 - 1) <= Ordinat(*movingObject) && Ordinat(*movingObject) <= (MAP_SIZE_Y / 2 + 1)) {
                        currentMap = 0;
                        Geser(movingObject,MAP_SIZE_X-3,0);
                        unicodeDraw(drawMode);
                    }
            }
            // Down arrow
            else if (Ordinat(*movingObject) == (MAP_SIZE_Y - 2) && input == 's') {
                if (isGraphConnected(mapGraph,1,3))
                    if ((MAP_SIZE_X / 2 - 3) <= Absis(*movingObject) && Absis(*movingObject) <= (MAP_SIZE_X / 2 + 1)) {
                        currentMap = 3;
                        Geser(movingObject,0,3-MAP_SIZE_Y);
                        unicodeDraw(drawMode);
                    }
            }
            else
                moveCursor(movingObject,input,collision);
            break;
        case 2:
            // Right arrow
            if (Absis(*movingObject) == (MAP_SIZE_X - 2) && input == 'd') {
                if (isGraphConnected(mapGraph,2,3))
                    if ((MAP_SIZE_Y / 2 - 1) <= Ordinat(*movingObject) && Ordinat(*movingObject) <= (MAP_SIZE_Y / 2 + 1)) {
                        currentMap = 3;
                        Geser(movingObject,3-MAP_SIZE_X,0); //-= (MAP_SIZE_X - 3);
                        unicodeDraw(drawMode);
                    }
            }
            // Up arrow
            else if (Ordinat(*movingObject) == 1 && input == 'w') {
                if (isGraphConnected(mapGraph,2,0))
                    if ((MAP_SIZE_X / 2 - 3) <= Absis(*movingObject) && Absis(*movingObject) <= (MAP_SIZE_X / 2 + 1)) {
                        currentMap = 0;
                        Geser(movingObject,0,MAP_SIZE_Y-3);
                        unicodeDraw(drawMode);
                    }
            }
            else
                moveCursor(movingObject,input,collision);
            break;
        case 3:
            // Top arrow
            if (Ordinat(*movingObject) == 1 && input == 'w') {
                if (isGraphConnected(mapGraph,3,1))
                    if ((MAP_SIZE_X / 2 - 3) <= Absis(*movingObject) && Absis(*movingObject) <= (MAP_SIZE_X / 2 + 1)) {
                        currentMap = 1;
                        Geser(movingObject,0,MAP_SIZE_Y-3);
                        unicodeDraw(drawMode);
                    }
            }
            // Left arrow
            else if (Absis(*movingObject) == 1 && input == 'a') {
                if (isGraphConnected(mapGraph,3,2))
                    if ((MAP_SIZE_Y / 2 - 1) <= Ordinat(*movingObject) && Ordinat(*movingObject) <= (MAP_SIZE_Y / 2 + 1)) {
                        currentMap = 2;
                        Geser(movingObject,MAP_SIZE_X-3,0);
                        unicodeDraw(drawMode);
                    }
            }
            else
                moveCursor(movingObject,input,collision);
            break;
    }
}


void buildingCollisionPrompt(int posX, int posY) {
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    printf("Ketik detail / repair / cancel");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    wordInput();
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    puts("                   ");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    puts("                                                 ");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    // Set cursor pos for repeated input, which can cause weird overwrite
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    if (stringCompare("detail",CurrentInput))
        printDetail(posX, posY, 2);
    else if (stringCompare("repair",CurrentInput))
        repairBuilding(posX, posY);
}

void officeCollisionPrompt() {
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    printf("Office, detail / laporan / cancel");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    wordInput();
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    puts("                   ");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    puts("                                                 ");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    // Set cursor pos for repeated input, which can cause weird overwrite
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    if (stringCompare("detail",CurrentInput))
        getDetails();
    else if (stringCompare("laporan",CurrentInput))
        getLaporan();
}

void queueCollisionPrompt() {
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    printf("Antrian, serve / cancel");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    wordInput();
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    puts("                   ");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
    puts("                                                 ");
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    // Set cursor pos for repeated input, which can cause weird overwrite
    setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
    if (stringCompare("serve",CurrentInput)) {
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
        if ((Durasi(currentTime,cPrepTime) % 1440 - SERVE_TIME) >= 0) {
            generateNewCustomer();
            customerPlayingCheck();
            customerTickCheck();
            serveCustomer(); // TODO : Completion
        }
        else
            puts("Maaf waktu tidak cukup");
    }
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
    currentTime = cPrepTime;
    currentState = 0;
    frameSet(1);
    forceDraw();
    draw();
    unicodeDraw(1);
    Absis(cursorLocation) = CURSOR_REST_X;
    Ordinat(cursorLocation) = CURSOR_REST_Y;
    // Preparation day loop
    while (true) {
        infoUpdate(1);
        mapUpdate(1);
        draw();

        // setCountMaterialByID(materialDatabase,10,10+getCountMaterialByID(materialDatabase,10)); // DEBUG
        // setCountMaterialByID(materialDatabase,11,10+getCountMaterialByID(materialDatabase,11));
        // setCountMaterialByID(materialDatabase,12,10+getCountMaterialByID(materialDatabase,12));
        // setCountMaterialByID(materialDatabase,13,10+getCountMaterialByID(materialDatabase,13));
        // setCountMaterialByID(materialDatabase,14,10+getCountMaterialByID(materialDatabase,14));


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
        if (stringCompare("build",CurrentInput))
            buildNewBuilding();
        else if (stringCompare("upgrade",CurrentInput))
            upgradeBuilding();
        else if (stringCompare("buy",CurrentInput))
            buyMaterial();
        else if (stringCompare("undo",CurrentInput)) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            switch (actionUndo()) {
                case 0:
                    puts("Tidak ada aksi yang dapat diundo");
                    break;
                case 1:
                    puts("Wahana telah dibakar");
                    break;
                case 2:
                    puts("Upgrade telah dicancel");
                    break;
                case 3:
                    puts("Pembelian telah dibatalkan");
                    break;
            }
        }
        else if (stringCompare("execute",CurrentInput)) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            puts("Apakah anda yakin untuk eksekusi aksi? (y/n)");
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
            wordInput();
            if (CurrentInput[0] == 'y') {
                actionTuple tempTrash;
                while (!IsEmpty(actionStack)) {
                    Pop(&actionStack,&tempTrash);
                    actionCount--;
                }
                currentMap = 0;
                break; // Break entire preparation day loop
            }
        }
        else if (stringCompare("main",CurrentInput)) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            puts("Apakah anda yakin untuk masuk play tanpa eksekusi? (y/n)");
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
            wordInput();
            if (CurrentInput[0] == 'y') {
                while (actionUndo());
                break;
            } // TODO : Port loading bar
        }
        // TODO : Total rework frame buffer
        else if (stringCompare("color",CurrentInput)) {
            colorSchemeChange(30);
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
        else if (stringCompare("db",CurrentInput)) {
            // DEBUG only
            setCountMaterialByID(materialDatabase,10,10+getCountMaterialByID(materialDatabase,10));
            setCountMaterialByID(materialDatabase,11,10+getCountMaterialByID(materialDatabase,11));
            setCountMaterialByID(materialDatabase,12,10+getCountMaterialByID(materialDatabase,12));
            setCountMaterialByID(materialDatabase,13,10+getCountMaterialByID(materialDatabase,13));
            setCountMaterialByID(materialDatabase,14,10+getCountMaterialByID(materialDatabase,14));
        }
        else if (stringCompare("detail",CurrentInput)) {
            if (entityAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) >= 20)
                printDetail(Ordinat(cursorLocation), Absis(cursorLocation), 1);
        }
        else if (stringCompare("repair",CurrentInput)) {
            if (entityAt(map[currentMap],Ordinat(cursorLocation),Absis(cursorLocation)) >= 20)
                repairBuilding(Ordinat(cursorLocation), Absis(cursorLocation));
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
            delay(1500);
            forceDraw();
            unicodeDraw(1);
        }
        else if (CurrentInput[0] == 'w' || CurrentInput[0] == 'a' || CurrentInput[0] == 's' || CurrentInput[0] == 'd') {
            moveMap(&cursorLocation, CurrentInput[0], 1, false);
        }
        CurrentInput[1] = '\0';
    }
}

void playDay() {
    currentTime = cPlayTime;
    currentState = 1;
    frameSet(2);
    mapUpdate(2);
    currentMap = playerMapLocation;
    entityAt(map[playerMapLocation],Ordinat(playerLocation),Absis(playerLocation)) = 0;
    occupiedAt(map[playerMapLocation],Ordinat(playerLocation),Absis(playerLocation)) = false;

    playPhaseSetup();

    forceDraw();
    draw();
    unicodeDraw(2);
    // LOOP
    while (true) {
        infoUpdate(2);
        mapUpdate(2);
        draw();

        if ((Durasi(currentTime,cPrepTime) % 1440 - MOVE_TIME) < 0) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
            queueElmtType tempTrash;
            while (Head(playQueue) != QueueNil)
                Dequeue(&playQueue,&tempTrash);
            break;
        }


        // Positioning for user input
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
        wordInput();
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
        puts("                   ");
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
        puts("                                                 ");
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y );
        puts("                                                 ");
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
        // Set cursor pos for repeated input, which can cause weird overwrite
        setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);



        // If input too long, force draw everything
        if (LengthInput > 15) {
            forceDraw();
            unicodeDraw(2);
        }


        if (stringCompare("color",CurrentInput)) {
            colorSchemeChange(30);
            forceDraw();
            unicodeDraw(2);
        }
        else if (stringCompare("legend",CurrentInput)) {
            printLegendList(1); // ??
            puts("Tekan enter untuk melanjutkan");
            wordInput();
            forceDraw();
            unicodeDraw(2);
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
                unicodeDraw(2);
            }
        }
        else if (stringCompare(key,CurrentInput)) {
            system(CLSCRN);
            money += 1000;
            setCursorPosition(0,0);
            puts(wait);
            puts(pressf);
            delay(1500);
            forceDraw();
            unicodeDraw(2);
        }
        else if (CurrentInput[0] == 'w' || CurrentInput[0] == 'a' || CurrentInput[0] == 's' || CurrentInput[0] == 'd') {
            if ((Durasi(currentTime,cPrepTime) % 1440 - MOVE_TIME) >= 0) {
                generateNewCustomer();
                customerPlayingCheck();
                customerTickCheck();
                moveMap(&playerLocation, CurrentInput[0], 2, true);
            }
            else {
                setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
                puts("Maaf waktu tidak cukup");
            }
        }
        else if (stringCompare("prepare",CurrentInput)) {
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+5, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            puts("Apakah anda yakin untuk mengosongkan antrian? (y/n)");
            setCursorPosition(MAP_OFFSET_X+MAP_SIZE_X+25, MAP_OFFSET_Y + MAP_SIZE_Y - 2);
            wordInput();
            if (CurrentInput[0] == 'y') {
                queueElmtType tempTrash;
                while (Head(playQueue) != QueueNil)
                    Dequeue(&playQueue,&tempTrash);
                break;
            }
                // TODO : Port loading bar
        }
        CurrentInput[1] = '\0';
    }
    // DEBUG
    // DEBUG STOP
    playerMapLocation = currentMap;
    entityAt(map[playerMapLocation],Ordinat(playerLocation),Absis(playerLocation)) = 1;
    occupiedAt(map[playerMapLocation],Ordinat(playerLocation),Absis(playerLocation)) = true;
    currentDay++;
}



// ----- Draw function set -----
// Every draw function which using argument int tp,
// these are meaning of those int values
// 0 Initialization
// 1 Preparation
// 2 Play

void printBuildList() {
    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+3);
    // First table
    puts(BUILD_TITLE);
    puts(BUILD_LIST_1);
    puts(BUILD_LIST_2);
    puts(BUILD_LIST_3);
    for (int i = 0 ; i < buildingCount ; i++)
        if (buildingDatabase[i].ID < 120)
            printf(BUILD_LIST_4, buildingDatabase[i].ID-19, buildingDatabase[i].nama, buildingDatabase[i].harga, buildingDatabase[i].durasi, buildingDatabase[i].kapasitas, buildingDatabase[i].deskripsi);

    puts(BUILD_LIST_5);
    // Second table
    // Procedural table generator
    printf(BUILD_MATERIAL_1);
    for (int i = 0 ; i < materialCount - 1 ; i++)
        printf(BUILD_MATERIAL_PROC_1);
    puts(BUILD_MATERIAL_PROC_1_END);
    printf(BUILD_MATERIAL_2);
    for (int i = 0 ; i < materialCount ; i++)
        printf(BUILD_MATERIAL_PROC_2,materialDatabase[i].nama);
    puts("");
    printf(BUILD_MATERIAL_3);
    for (int i = 0 ; i < materialCount - 1 ; i++)
        printf(BUILD_MATERIAL_PROC_3);
    printf(BUILD_MATERIAL_PROC_3_END);
    for (int i = 0 ; i < buildingCount ; i++) {
        if (buildingDatabase[i].ID < 120) {
            printf(BUILD_MATERIAL_4,buildingDatabase[i].ID-19, buildingDatabase[i].nama);
            for (int j = 0 ; j < materialCount ; j++) {
                if (buildingDatabase[i].materialArray[j] > materialDatabase[j].material_count)
                    printf("\33\[31m\33\[2m");
                else
                    printf("\33\[32m\33\[1m");
                printf(BUILD_MATERIAL_PROC_INNER,buildingDatabase[i].materialArray[j]);
            }
            printf("\33\[m\n");
        }
    }
    printf(BUILD_MATERIAL_5);
    for (int i = 0 ; i < materialCount - 1 ; i++) {
        printf(BUILD_MATERIAL_PROC_4);
    }
    printf(BUILD_MATERIAL_PROC_4_END);

    puts("Masukkan ID yang ingin dibangun :");
}

void printUpgradeList(int buildingIndex){
    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+3);
    // First Table
    MakePohonUpgrade(&upgradeDatabase,buildingCount); // FIXME : Temporary fix
    puts(UPGRADE_TITLE);
    printf(UPGRADE_LIST_1);
    for (int i = 0 ; i < materialCount - 1 ; i++)
        printf(UPGRADE_MATERIAL_PROC_1);
    puts(UPGRADE_MATERIAL_PROC_1_END);
    printf(UPGRADE_LIST_2);
    for (int i = 0 ; i < materialCount ; i++)
        printf(UPGRADE_MATERIAL_PROC_2,materialDatabase[i].nama);
    printf(UPGRADE_LIST_3);
    for (int i = 0 ; i < materialCount - 1 ; i++)
        printf(UPGRADE_MATERIAL_PROC_3);
    puts(UPGRADE_MATERIAL_PROC_3_END);
    int leftUpgrade = Akar(Left(upgradeDatabase[buildingIndex]));
    int rightUpgrade = Akar(Right(upgradeDatabase[buildingIndex]));
    int leftIndex = getIndexByID(buildingDatabase, leftUpgrade);
    int rightIndex = getIndexByID(buildingDatabase, rightUpgrade);

    printf(UPGRADE_LIST_4, 1, buildingDatabase[leftIndex].nama, buildingDatabase[leftIndex].harga, buildingDatabase[leftIndex].durasi, buildingDatabase[leftIndex].kapasitas);
    for (int i = 0 ; i < materialCount ; i++) {
        if (buildingDatabase[leftIndex].materialArray[i] > materialDatabase[i].material_count)
            printf("\33\[31m\33\[2m");
        else
            printf("\33\[32m\33\[1m");
        printf(UPGRADE_MATERIAL_PROC_INNER,buildingDatabase[leftIndex].materialArray[i]);
    }
    printf("\33\[m\n");

    printf(UPGRADE_LIST_4, 2, buildingDatabase[rightIndex].nama, buildingDatabase[rightIndex].harga, buildingDatabase[rightIndex].durasi, buildingDatabase[rightIndex].kapasitas);
    for (int i = 0 ; i < materialCount ; i++) {
        if (buildingDatabase[rightIndex].materialArray[i] > materialDatabase[i].material_count)
            printf("\33\[31m\33\[2m");
        else
            printf("\33\[32m\33\[1m");
        printf(UPGRADE_MATERIAL_PROC_INNER,buildingDatabase[rightIndex].materialArray[i]);
    }
    printf("\n");

    printf(UPGRADE_LIST_5);
    for (int i = 0 ; i < materialCount - 1 ; i++) {
        printf(UPGRADE_MATERIAL_PROC_4);
    }
    printf(UPGRADE_MATERIAL_PROC_4_END);
    puts("Masukkan ID upgrade yang diinginkan :");
}

void printDetail(int posX, int posY, int tp) {
    // TODO : Collision
    setCursorPosition(0, MAP_OFFSET_Y + MAP_SIZE_Y + 3);
    Wahana selectedBuilding = *buildingAt(map[currentMap], posX, posY);
    POINT buildingLocation = MakePOINT(posY,posX); // DEBUG
    puts(DETAIL_TITLE);
    puts(DETAIL_LIST_1);
    puts(DETAIL_LIST_2);
    puts(DETAIL_LIST_3);
    char statusBuilding[10], upgradeStatus[25], historyUpgrade[16];

    if (selectedBuilding.statusWahana)
        stringCopy("Berfungsi",statusBuilding);
    else
        stringCopy("Rusak",statusBuilding);

    if (LinIsEmpty(selectedBuilding.upgrade)) {
        stringCopy("Tidak ada",upgradeStatus);
        stringCopy("Tidak ada",historyUpgrade);
    }
    else {
        int upgradeIndex = getIndexByID(buildingDatabase, Info(First(selectedBuilding.upgrade)));
        stringCopy(buildingDatabase[upgradeIndex].nama, upgradeStatus);
        stringCopy("Tidak ada",historyUpgrade); // TODO : ???
    }

    printf(DETAIL_LIST_4, selectedBuilding.ID, selectedBuilding.nama, Absis(buildingLocation), Ordinat(buildingLocation), upgradeStatus, historyUpgrade, statusBuilding);
    puts(DETAIL_LIST_5);
    puts("Tekan enter untuk melanjutkan");
    wordInput();
    forceDraw(tp);
    unicodeDraw(tp);
}

void printMaterialList() {
    setCursorPosition(0,MAP_OFFSET_Y+MAP_SIZE_Y+3);
    puts(MATERIAL_TITLE);
    puts(MATERIAL_LIST_1);
    puts(MATERIAL_LIST_2);
    puts(MATERIAL_LIST_3);
    for (int i = 0 ; i < materialCount ; i++)
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
        printf(LEGEND_LIST_4,'*', "Kursor Pembangun");
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
                    printf(LEGEND_LIST_4,'@', "Pemain"); // TODO Maybe unsorted
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

void colorSchemeChange(int tdelay) {
    system(CLSCRN);
    setCursorPosition(0,0);
    puts("Color scheme :");
    puts("1. Black");
    puts("2. White");
    printf(">> ");
    wordInput();
    if (stringCompare("black",CurrentInput) || CurrentInput[0] == '1') {
        puts("Processing ...");
        drawLoading(tdelay);
        puts(colorScheme[1]);
        currentColorScheme = 1;
    }
    else if (stringCompare("white",CurrentInput) || CurrentInput[0] == '2') {
        puts("Processing ...");
        drawLoading(tdelay);
        puts(colorScheme[2]);
        currentColorScheme = 2;
    }
    else
        puts("Masukkan tidak diketahui");
}

void frameSet(int tp) { // TODO : Possible merge with other frame function
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
        // Wipe old record
        for (int i = 0 ; i < 5 ; i++)
            for (int j = 0 ; j < INFO_SIZE_X ; j++)
                infoframe[7+i][j] = ' ';
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
        // Wipe old record
        for (int i = 0 ; i < 5 ; i++)
            for (int j = 0 ; j < INFO_SIZE_X ; j++)
                infoframe[7+i][j] = ' ';
        infoBlock[4] = "Closing time   | ";
        infoBlock[6] = "     ---------------  Queue -----------------     ";
        char* queueBlock;
        queueBlock = "                                                  ";
        for (int i = 0 ; i < 5 ; i++)
            for (int j = 0 ; j < INFO_BLOCK_SIZE ; j++)
                infoframe[7+i][j] = queueBlock[j];
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
        infoframe[4][INFO_BLOCK_SIZE+i+1] = endTime[i];
    // FIXME : ??

    for (int i = 0 ; i < INFO_SIZE_X ; i++) {
        infoframe[6][i] = infoBlock[6][i];
        infoframe[12][i] = infoBlock[7][i];
        infoframe[13][i] = infoBlock[8][i];
    }

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
    // TODO : Cut day from preparation and play

    // Border
    for (int i = 0 ; i < MAP_SIZE_Y ; i++) {
        setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X - 1, MAP_OFFSET_Y + i);
        puts("\33\[90m\u2588\33\[m");
        setCursorPosition(MAP_OFFSET_X, MAP_OFFSET_Y + i);
        puts("\33\[90m\u2588\33\[m");
    }

    for (int i = 0 ; i < MAP_SIZE_X ; i++) {
        setCursorPosition(MAP_OFFSET_X + i, MAP_OFFSET_Y);
        puts("\33\[90m\u2584\33\[m");
        setCursorPosition(MAP_OFFSET_X + i, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
        puts("\33\[90m\u2580\33\[m");
    }


    switch (currentMap) {
        case 0:
            // Right arrow
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X - 1, MAP_OFFSET_Y + MAP_SIZE_Y/2);
            puts("\33\[93m\33\[1m\u2192\33\[m");
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X - 1, MAP_OFFSET_Y + MAP_SIZE_Y/2 - 1);
            puts("\33\[93m\33\[1m\u2192\33\[m");
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X - 1, MAP_OFFSET_Y + MAP_SIZE_Y/2 + 1);
            puts("\33\[93m\33\[1m\u2192\33\[m");

            // Down arrow
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X / 2 - 3, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            puts("\33\[93m\33\[1m\u2193\u2193\u2193\u2193\u2193\33\[m");
            break;
        case 1:
            // Down arrow
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X / 2 - 3, MAP_OFFSET_Y + MAP_SIZE_Y - 1);
            puts("\33\[93m\33\[1m\u2193\u2193\u2193\u2193\u2193\33\[m");

            // Left arrow
            setCursorPosition(MAP_OFFSET_X, MAP_OFFSET_Y + MAP_SIZE_Y/2);
            puts("\33\[93m\33\[1m\u2190\33\[m");
            setCursorPosition(MAP_OFFSET_X, MAP_OFFSET_Y + MAP_SIZE_Y/2 - 1);
            puts("\33\[93m\33\[1m\u2190\33\[m");
            setCursorPosition(MAP_OFFSET_X, MAP_OFFSET_Y + MAP_SIZE_Y/2 + 1);
            puts("\33\[93m\33\[1m\u2190\33\[m");
            break;
        case 2:
            // Top arrow
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X / 2 - 3, MAP_OFFSET_Y);
            puts("\33\[93m\33\[1m\u2191\u2191\u2191\u2191\u2191\33\[m");

            // Down arrow
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X - 1, MAP_OFFSET_Y + MAP_SIZE_Y/2);
            puts("\33\[93m\33\[1m\u2192\33\[m");
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X - 1, MAP_OFFSET_Y + MAP_SIZE_Y/2 - 1);
            puts("\33\[93m\33\[1m\u2192\33\[m");
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X - 1, MAP_OFFSET_Y + MAP_SIZE_Y/2 + 1);
            puts("\33\[93m\33\[1m\u2192\33\[m");
            break;
        case 3:
            // Top arrow
            setCursorPosition(MAP_OFFSET_X + MAP_SIZE_X / 2 - 3, MAP_OFFSET_Y);
            puts("\33\[93m\33\[1m\u2191\u2191\u2191\u2191\u2191\33\[m");

            // Left arrow
            setCursorPosition(MAP_OFFSET_X, MAP_OFFSET_Y + MAP_SIZE_Y/2);
            puts("\33\[93m\33\[1m\u2190\33\[m");
            setCursorPosition(MAP_OFFSET_X, MAP_OFFSET_Y + MAP_SIZE_Y/2 - 1);
            puts("\33\[93m\33\[1m\u2190\33\[m");
            setCursorPosition(MAP_OFFSET_X, MAP_OFFSET_Y + MAP_SIZE_Y/2 + 1);
            puts("\33\[93m\33\[1m\u2190\33\[m");
            break;
    }


    // Information UNICODE overwrite
    setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y-1);
    puts(INFO_UNICODE);

    int middleLineDrawLimit;
    if (tp == 0 || tp == 1)
        middleLineDrawLimit = 12;
    else if (tp == 2)
        middleLineDrawLimit = 6;
    for (int i = 0 ; i < middleLineDrawLimit ; i++) {
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

    setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+13);
    puts(INFO_BROKEN_BUILDING); // TODO : Add broken building
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
            setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+12);
            puts(INFO_WINDOW_SEP);
            break;
        case 2:
            setCursorPosition(INFO_OFFSET_X+10,INFO_OFFSET_Y-4);
            puts(PLAY_DAY_TITLE_1);
            setCursorPosition(INFO_OFFSET_X+10,INFO_OFFSET_Y-3);
            puts(PLAY_DAY_TITLE_2);
            setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+6);
            puts(INFO_PLAY_WINDOW);
            setCursorPosition(INFO_OFFSET_X-1,INFO_OFFSET_Y+12);
            puts(INFO_WINDOW_SEP_PLAY);
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

void draw() {
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
