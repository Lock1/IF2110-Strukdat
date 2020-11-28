/*
13519214, Game engine
mostly steal and rewritten on C for linux
source: from my shitty C++ and windows-based game lul
*/


// ------------------ Macro and Library ------------------
#ifndef ENGINE_H
#define ENGINE_H

// Standard C Library
#include <stdio.h>
#include <stdlib.h>

// User library
#include "config.h"
#include "structure/boolean.h"
#include "structure/mesinkata.h"
#include "structure/jam.h"
#include "structure/matrix.h"
#include "structure/point.h"
#include "structure/stack.h"
#include "structure/graph.h"
#include "structure/tree.h"
#include "structure/listlinear.h"
#include "structure/listarray.h"
#include "structure/prioqueuechar.h"


#include "fileio.h"

// -------------------------------------------------------
// Player name (line 1)
// Money (line 2)
// Time (line 3-5) (start, elapsed, stop)
// Queue (line 6-12) (2 line for border, 5 for actual queue)
// Broken building (line 13-15)

// ---------------- Function Declaration -----------------
// xxx----- Internal engine function -----xxx
// NOT RECOMMENDED FOR USAGE OUTSIDE ENGINE.C
void setCursorPosition(int XPos, int YPos);
// Setting cursor to XPos and YPos
void stringCopy(char* src, char* dst);
// Copying string to destination
boolean stringCompare(char* st1, char* st2);
// Comparing 2 string and return true if equal
boolean integerInput(int *store);
// Asking for user input
void delay(int limit);
// Delaying by count
// xxx------------------------------------xxx


// xxx----- External function -----xxx
boolean startGame();
// Checking for save or new game

// xxx----- Internal function -----xxx
void prepDay();

void playDay();

void endGame();

void colorSchemeChange();

// ------------ Database Procedures ------------
void loadDatabase();

void loadMap();



// ------------- Action Procedures ------------
int actionUndo();

void buildNewBuilding(void);

void buyMaterial(void);

void upgradeBuilding(void);

void getDetails();

void getLaporan();

void repairBuilding(int posX, int posY);

void destroy();



// ------------ Movement Procedures ------------
void moveCursor(POINT* movingObject, char input, boolean collision);
// If not move map, then check collision / just move

void moveMap(POINT* movingObject, char input, int drawMode, boolean collision);
// Movement with map checking

void buildingCollisionPrompt(int posX, int posY);
// Prompting user repair or detail





// -------- Drawing Procedures ---------
// -- List drawing procedures --
void printBuildList();

void printUpgradeList();

void printMaterialList();

void printLegendList();

void printDetail();
// Creating list and draw on screen

void infoUpdate(int tp);
// Update frame with changes in information screen

void mapUpdate();
// Update frame with changes in map

void drawLoading();
// Draw loading bar

void frameSet(int tp);
// Setting frame with respective mode

void unicodeDraw();
// Single draw only, force draw but only for unicode char

void draw();
// Draw frame on screen with double buffering
/* Note : Like old project, implemented with double buffer
in order to avoid flickering issues */

void forceDraw();
// Forcefully draw old frame
/* Note : Avoid using it on loop, can cause massive
flickering issues with uncontrolled call */

// xxx------------------------------------xxx
// -------------------------------------------------------

#endif
