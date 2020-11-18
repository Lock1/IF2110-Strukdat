// 13519214, Game configuration
// Default configuration
#define RES_X 115
#define RES_Y 29
#define MAP_OFFSET_X 4
#define MAP_OFFSET_Y 2
#define MAP_SIZE_X 50
#define MAP_SIZE_Y 25
#define INFO_OFFSET_X 60
#define INFO_OFFSET_Y 4
#define INFO_SIZE_X 50
#define INFO_SIZE_Y 16
#define INFO_BLOCK_SIZE 16

// Other configuration
#define IC 1000000 // Instruction clock
#define START_MONEY 100
#define START_PLAY 9
#define START_PREP 21
#define STRING_LENGTH 50

// Debugging feature
#define DEBUG 1
#define DEBUG_HEADER

// Target system macro
// #ifdef WIN
//     #include <Windows.h>
//     #define CLSCRN "cls"
// #else
//     #include <unistd.h>     // Needed for sleep()
    #define CLSCRN "clear"  // Target system clear screen command
// #endif

// Debugging macro
#define dpf(sform,...) if (DEBUG) printf(sform,__VA_ARGS__);
#define dp(s) if (DEBUG) puts(s);
// #ifdef DEBUG_HEADER
//     #include <time.h>
// #endif
