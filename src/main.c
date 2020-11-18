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
    if (startGame()) {
        // Give user time to seeing ASCII ART
        delay(1000);

        // Initial frame setup
        frameSet();
        infoUpdate();
        mapUpdate();
        forceDraw();

        // DEBUG
        long long int fpush = 0;
        // DEBUG STOP

        // Game loop
        while (true) {
            delay(1);
            infoUpdate();
            mapUpdate();
            draw();
            // wordInput();

            // DEBUG
            dpf("    |||<%lld frames pushed>|||    ",++fpush);
            setCursorPosition(60,26);
            dp("    +--------< DEBUG >---------+    ");
            // DEBUG STOP
        }
    }

    return 0;
}
