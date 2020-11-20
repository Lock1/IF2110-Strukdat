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
        drawLoading(100);

        // Initial frame setup
        frameSet(0);
        infoUpdate(0);
        mapUpdate(1);
        forceDraw();

        // Game loop
        while (true) {
            draw();
            prepDay();
            playDay();
        }
    }
    else
        endGame();
    return 0;
}
