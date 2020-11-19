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
// xxx------------------------------------xxx


// xxx----- External engine function -----xxx
// TODO : Input

// TODO : Whole lot of update function

// TODO : Maybe also tick update
// TODO : Use some seed for rng (probably username also fine lul)

boolean startGame();
// Checking for save and newgame

void prepDay();

void playDay();

void frameSet();

void loadMap();

void printBuildList();

void loadDatabase();

void infoUpdate();
// Update frame with changes in information screen

void mapUpdate();
// Update frame with changes in map

void delay(int limit);
// Delaying by count

void unicodeDraw();

void draw();
// Draw frame on screen with double buffering
/* Note : Like my C++, implemented with double buffer
in order to avoid flickering issues */

void forceDraw();
// Forcefully draw old frame
/* Note : Avoid using it on loop, can cause massive
flickering issues with uncontrolled call */

// xxx------------------------------------xxx
// -------------------------------------------------------

#endif
