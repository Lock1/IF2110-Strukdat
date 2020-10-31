/* 13519214, Game engine
mostly steal and rewritten on C for linux
source: from my shitty C++ and windows-based game lul
*/


// ------------------ Macro and Library ------------------
// C Library
#include <stdio.h>
#include <stdlib.h>

// User library
#include "structure/boolean.h"

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
void SetCursorPosition(int XPos, int YPos);
// Engine
void mapUpdate();
void forceDraw();
void draw();
// TODO: add description
// -------------------------------------------------------
