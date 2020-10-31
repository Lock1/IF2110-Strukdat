/* Game engine, 13519214
mostly steal and rewritten for linux
source: from my shitty game lul
*/



// ------------------ Macro and Library ------------------
// C Library
#include <stdio.h>
#include <stdlib.h>

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



// --- Function declaration ----
void draw();
// TODO: add description
