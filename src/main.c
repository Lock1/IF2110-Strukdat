/*
----------------------------------------------
-- Tugas Besar Algoritma dan Struktur Data ---
------------ Kelas 2 - Kelompok 4 ------------
| 13519046    Dwianditya Hanif Raharjanto    |
| 13519110        Mohammad Afif Akromi       |
| 13519146         Fadel Ananda Dotty        |
| 13519206      Muhammad Fawwaz Naabigh      |
| 13519214      Tanur Rizaldi Rahardjo       |
----------------------------------------------
*/

// Dev
// Tags used : TODO, DEBUG, FIXME
// Macro : DEBUG

// Library
#include "engine.h"

int main(void) {
    system(CLSCRN);
    // TODO: Main menu
    if (startGame()) {
        long long int clock = 0, count = 0;
        while (count != 10) {
            while (clock != IC*100)
                clock++;
            clock = 0;
            count++;
        }
        count = 0;
        // Game loop
        frameSet();
        // mapUpdate();
        forceDraw();
        // DEBUG
        long long int fpush = 0;
        // DEBUG STOP
        while (true) {
            if (clock % IC == 0) {
                infoUpdate();
                mapUpdate();
                draw();
                dpf("    |||<%lld frames pushed>|||    ",++fpush);
                setCursorPosition(60,26);
                dp("    +--------< DEBUG >---------+    ");
                clock = 0;
            }
            clock++;
        }
    }
    return 0;
}
