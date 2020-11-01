/*
13519214, Game engine
mostly steal and rewritten on C for linux
source: from my shitty C++ and windows-based game lul
*/


// ------------------ Macro and Library ------------------
// Standard C Library
#include <stdio.h>
#include <stdlib.h>

// User library
#include "structure/boolean.h"

// Default configuration
#define RES_X 115
#define RES_Y 29
#define MAP_OFFSET_X 4
#define MAP_OFFSET_Y 2
#define MAP_SIZE_X 50
#define MAP_SIZE_Y 25

// Debugging feature
#define DEBUG 1

// Target system macro
#ifdef WIN
    #include <Windows.h>
    #define CLSCRN "cls"
#else
    #include <unistd.h>     // Needed for sleep()
    #define CLSCRN "clear"  // Target system clear screen command
#endif

// Debugging macro
#define dpf(sform,...) if (DEBUG) printf(sform,__VA_ARGS__);
#define dp(s) if (DEBUG) puts(s);
// -------------------------------------------------------


// ---------------- Function Declaration -----------------
// xxx----- Internal engine function -----xxx
// NOT RECOMMENDED FOR USAGE OUTSIDE ENGINE.C
void setCursorPosition(int XPos, int YPos);
// Setting cursor to XPos and YPos
// xxx------------------------------------xxx


// xxx----- External engine function -----xxx
// TODO : Input

// TODO : Whole lot of update function

// TODO : Maybe also tick update
// TODO : Use some seed for rng (probably username also fine lul)

void frameSet();

void mapUpdate();
// Update frame with changes in map


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
