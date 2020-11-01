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

// Library
#include "engine.h"

int main(void) {
    system(CLSCRN);
    // TODO: Main menu

    // Game loop
    frameSet();
    forceDraw();
    sleep(1);
    while (true) {
        mapUpdate();
        draw();
        sleep(0.9);
    }
    return 0;
}
