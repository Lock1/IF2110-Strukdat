// 13519214, Game configuration
// Default configuration
#define RES_X 115
#define RES_Y 29
#define MAP_OFFSET_X 4
#define MAP_OFFSET_Y 2
#define MAP_SIZE_X 50
#define MAP_SIZE_Y 25
#define INFO_OFFSET_X 63
#define INFO_OFFSET_Y 6
#define INFO_SIZE_X 50
#define INFO_SIZE_Y 17
#define INFO_BLOCK_SIZE 16

// Other configuration
#define IC 1000000 // Instruction clock
#define START_MONEY 100
#define START_PLAY 9
#define START_PREP 21
#define STRING_LENGTH 50
#define CURSOR_REST_X 1
#define CURSOR_REST_Y 1

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



// ASCII Art
#define START_MENU_ASCII_ART "\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2580\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\n\u2588\u2584\u2500\u2588\u2580\u2580\u2580\u2588\u2500\u2584\u2588\u2584\u2500\u2584\u2584\u2500\u2588\u2584\u2500\u2584\u2588\u2588\u2588\u2500\u2584\u2584\u2584\u2500\u2588\u2500\u2584\u2584\u2500\u2588\u2584\u2500\u2580\u2588\u2580\u2500\u2584\u2588\u2584\u2500\u2584\u2584\u2500\u2588\u2588\u2588\u2500\u2584\u2500\u2584\u2500\u2588\u2500\u2584\u2584\u2500\u2588\u2588\u2588\u2584\u2500\u2588\u2580\u2580\u2580\u2588\u2500\u2584\u2588\u2588\u2580\u2584\u2500\u2588\u2588\u2584\u2500\u2580\u2588\u2584\u2500\u2584\u2588\u2500\u2584\u2584\u2584\u2584\u2588\u2584\u2500\u2588\u2500\u2584\u2588\u2584\u2500\u2588\u2500\u2584\u2588\u2591\u2588\u2500\u2584\u2584\u2584\u2584\u2588\n\u2588\u2588\u2500\u2588\u2500\u2588\u2500\u2588\u2500\u2588\u2588\u2588\u2500\u2584\u2588\u2580\u2588\u2588\u2500\u2588\u2588\u2580\u2588\u2500\u2588\u2588\u2588\u2580\u2588\u2500\u2588\u2588\u2500\u2588\u2588\u2500\u2588\u2584\u2588\u2500\u2588\u2588\u2588\u2500\u2584\u2588\u2580\u2588\u2588\u2588\u2588\u2588\u2500\u2588\u2588\u2588\u2500\u2588\u2588\u2500\u2588\u2588\u2588\u2588\u2500\u2588\u2500\u2588\u2500\u2588\u2500\u2588\u2588\u2588\u2500\u2580\u2500\u2588\u2588\u2588\u2500\u2588\u2584\u2580\u2500\u2588\u2588\u2500\u2588\u2588\u2584\u2500\u2588\u2588\u2500\u2584\u2580\u2588\u2588\u2588\u2584\u2500\u2584\u2588\u2588\u2584\u2588\u2584\u2584\u2584\u2584\u2500\u2588\n\u2580\u2580\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2580\u2580\u2584\u2584\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2584\u2584\u2580\u2580\u2580\u2580\u2584\u2584\u2584\u2580\u2580\u2584\u2584\u2584\u2584\u2580\u2580\u2580\u2580\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2580\u2580\u2584\u2584\u2580\u2584\u2584\u2580\u2584\u2584\u2584\u2580\u2580\u2584\u2584\u2580\u2584\u2584\u2584\u2584\u2584\u2580\u2584\u2584\u2580\u2584\u2584\u2580\u2580\u2584\u2584\u2584\u2580\u2580\u2580\u2580\u2584\u2584\u2584\u2584\u2584\u2580\n\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\n\u2588\u2584\u2500\u2588\u2580\u2580\u2580\u2588\u2500\u2584\u2588\u2500\u2584\u2584\u2500\u2588\u2584\u2500\u2584\u2584\u2580\u2588\u2584\u2500\u2584\u2588\u2588\u2588\u2584\u2500\u2584\u2584\u2580\u2588\n\u2588\u2588\u2500\u2588\u2500\u2588\u2500\u2588\u2500\u2588\u2588\u2500\u2588\u2588\u2500\u2588\u2588\u2500\u2584\u2500\u2584\u2588\u2588\u2500\u2588\u2588\u2580\u2588\u2588\u2500\u2588\u2588\u2500\u2588\n\u2580\u2580\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2580\u2580\u2584\u2584\u2584\u2584\u2580\u2584\u2584\u2580\u2584\u2584\u2580\u2584\u2584\u2584\u2584\u2584\u2580\u2584\u2584\u2584\u2584\u2580\u2580"

#define HAVE_FUN_ASCII_ART "\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2557\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2557\u2591\u2591\u2591\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2003\u2003\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2557\u2591\u2591\u2591\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2557\u2588\u2588\u2588\u2557\u2591\u2591\u2588\u2588\u2557\n\u2588\u2588\u2554\u2550\u2550\u2550\u2550\u255d\u2588\u2588\u2554\u2550\u2550\u2550\u2550\u255d\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2551\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2557\u255a\u2550\u2550\u2588\u2588\u2554\u2550\u2550\u255d\u2003\u2003\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2557\u2588\u2588\u2554\u2550\u2550\u2550\u2550\u255d\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2551\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2557\u2588\u2588\u2551\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2551\n\u255a\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2551\u2588\u2588\u2554\u2588\u2588\u2588\u2588\u2554\u2588\u2588\u2551\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2551\u2591\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2003\u2003\u2588\u2588\u2588\u2588\u2588\u2588\u2566\u255d\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2554\u255d\u2588\u2588\u2554\u2588\u2588\u2588\u2588\u2554\u2588\u2588\u2551\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2551\u2588\u2588\u2551\u2588\u2588\u2554\u2588\u2588\u2557\u2588\u2588\u2551\n\u2591\u255a\u2550\u2550\u2550\u2588\u2588\u2557\u2588\u2588\u2554\u2550\u2550\u255d\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2551\u2588\u2588\u2551\u255a\u2588\u2588\u2554\u255d\u2588\u2588\u2551\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2551\u2591\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2003\u2003\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2557\u2588\u2588\u2554\u2550\u2550\u255d\u2591\u2591\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2557\u2588\u2588\u2551\u255a\u2588\u2588\u2554\u255d\u2588\u2588\u2551\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2551\u2588\u2588\u2551\u2588\u2588\u2551\u255a\u2588\u2588\u2588\u2588\u2551\n\u2588\u2588\u2588\u2588\u2588\u2588\u2554\u255d\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2551\u2591\u2591\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u255a\u2550\u255d\u2591\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2003\u2003\u2588\u2588\u2588\u2588\u2588\u2588\u2566\u255d\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2551\u2591\u2591\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u255a\u2550\u255d\u2591\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u2591\u2588\u2588\u2551\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u255a\u2588\u2588\u2588\u2551\n\u255a\u2550\u2550\u2550\u2550\u2550\u255d\u2591\u255a\u2550\u2550\u2550\u2550\u2550\u2550\u255d\u255a\u2550\u2550\u2550\u2550\u2550\u2550\u255d\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u255d\u255a\u2550\u255d\u2591\u2591\u2591\u2591\u2591\u255a\u2550\u255d\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u2591\u2003\u2003\u255a\u2550\u2550\u2550\u2550\u2550\u255d\u2591\u255a\u2550\u2550\u2550\u2550\u2550\u2550\u255d\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u255d\u255a\u2550\u255d\u2591\u2591\u2591\u2591\u2591\u255a\u2550\u255d\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u255d\u255a\u2550\u255d\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u2550\u255d"

#define WILLY_WANGKY_ASCII_ART "\u2591\u2588\u2588\u2557\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2557\u2588\u2588\u2557\u2588\u2588\u2557\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2557\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2557\u2591\u2591\u2591\u2588\u2588\u2557\u2591\u2588\u2588\u2557\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2557\u2591\u2591\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2557\u2591\u2591\u2588\u2588\u2557\u2588\u2588\u2557\u2591\u2591\u2591\u2588\u2588\u2557\n\u2591\u2588\u2588\u2551\u2591\u2591\u2588\u2588\u2557\u2591\u2591\u2588\u2588\u2551\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u255a\u2588\u2588\u2557\u2591\u2588\u2588\u2554\u255d\u2591\u2588\u2588\u2551\u2591\u2591\u2588\u2588\u2557\u2591\u2591\u2588\u2588\u2551\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2557\u2591\u2588\u2588\u2551\u2588\u2588\u2554\u2550\u2550\u2550\u2550\u255d\u2591\u2588\u2588\u2551\u2591\u2588\u2588\u2554\u255d\u255a\u2588\u2588\u2557\u2591\u2588\u2588\u2554\u255d\n\u2591\u255a\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2554\u255d\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u2591\u255a\u2588\u2588\u2588\u2588\u2554\u255d\u2591\u2591\u255a\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2554\u255d\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2551\u2588\u2588\u2554\u2588\u2588\u2557\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u2591\u2588\u2588\u2557\u2591\u2588\u2588\u2588\u2588\u2588\u2550\u255d\u2591\u2591\u255a\u2588\u2588\u2588\u2588\u2554\u255d\u2591\n\u2591\u2591\u2588\u2588\u2588\u2588\u2554\u2550\u2588\u2588\u2588\u2588\u2551\u2591\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u255a\u2588\u2588\u2554\u255d\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2554\u2550\u2588\u2588\u2588\u2588\u2551\u2591\u2588\u2588\u2554\u2550\u2550\u2588\u2588\u2551\u2588\u2588\u2551\u255a\u2588\u2588\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u2591\u255a\u2588\u2588\u2557\u2588\u2588\u2554\u2550\u2588\u2588\u2557\u2591\u2591\u2591\u255a\u2588\u2588\u2554\u255d\u2591\u2591\n\u2591\u2591\u255a\u2588\u2588\u2554\u255d\u2591\u255a\u2588\u2588\u2554\u255d\u2591\u2588\u2588\u2551\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2557\u2591\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\u2591\u2591\u255a\u2588\u2588\u2554\u255d\u2591\u255a\u2588\u2588\u2554\u255d\u2591\u2588\u2588\u2551\u2591\u2591\u2588\u2588\u2551\u2588\u2588\u2551\u2591\u255a\u2588\u2588\u2588\u2551\u255a\u2588\u2588\u2588\u2588\u2588\u2588\u2554\u255d\u2588\u2588\u2551\u2591\u255a\u2588\u2588\u2557\u2591\u2591\u2591\u2588\u2588\u2551\u2591\u2591\u2591\n\u2591\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u255d\u255a\u2550\u2550\u2550\u2550\u2550\u2550\u255d\u255a\u2550\u2550\u2550\u2550\u2550\u2550\u255d\u2591\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u2591\u2591\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u255d\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u2550\u255d\u2591\u255a\u2550\u2550\u2550\u2550\u2550\u255d\u2591\u255a\u2550\u255d\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u2591\u255a\u2550\u255d\u2591\u2591\u2591"

#define PREP_DAY_TITLE_1 "\u2588\u2580\u2588\u2003\u2588\u2580\u2588\u2003\u2588\u2580\u2580\u2003\u2588\u2580\u2588\u2003\u2584\u2580\u2588\u2003\u2588\u2580\u2588\u2003\u2584\u2580\u2588\u2003\u2580\u2588\u2580\u2003\u2588\u2003\u2588\u2580\u2588\u2003\u2588\u2584\u2591\u2588\u2003 \u2003\u2588\u2580\u2584\u2003\u2584\u2580\u2588\u2003\u2588\u2584\u2588"
#define PREP_DAY_TITLE_2 "\u2588\u2580\u2580\u2003\u2588\u2580\u2584\u2003\u2588\u2588\u2584\u2003\u2588\u2580\u2580\u2003\u2588\u2580\u2588\u2003\u2588\u2580\u2584\u2003\u2588\u2580\u2588\u2003\u2591\u2588\u2591\u2003\u2588\u2003\u2588\u2584\u2588\u2003\u2588\u2591\u2580\u2588\u2003 \u2003\u2588\u2584\u2580\u2003\u2588\u2580\u2588\u2003\u2591\u2588\u2591"

#define BUILD_LIST_1 "\u250E\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2512"
#define BUILD_LIST_2 "\u2503%50s                                             \u2503\n"
#define BUILD_LIST_3 "\u2520\u2500\u2500\u2500\u2500\u2530\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2530\u2500\u2500\u2500\u2500\u2530\u2500\u2500\u2500\u2500\u2530\u2500\u2500\u2500\u2500\u2530\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2528"
#define BUILD_LIST_4 "\u2503 %d \u2503 %-20s \u2503 %-2d \u2503 %-2d \u2503 %-2d \u2503 %-50s \u2503\n"
#define BUILD_LIST_5 "\u2516\u2500\u2500\u2500\u2500\u2538\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2538\u2500\u2500\u2500\u2500\u2538\u2500\u2500\u2500\u2500\u2538\u2500\u2500\u2500\u2500\u2538\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u251A"

#define what "\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2591\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\n\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591\u2591"
