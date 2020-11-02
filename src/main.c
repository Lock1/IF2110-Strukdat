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
    enableRawMode(); // EXPERIMENTAL
    // Game loop
    frameSet();
    mapUpdate();
    forceDraw();
    sleep(1);
    // DEBUG
    long long int fpush = 0;
    time_t tstart = time(NULL), tc = time(NULL);
    // DEBUG STOP
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // EXPERIMENTAL
    while (true) {
        usleep(1);
        // usleep(1024); // TODO : They say, usleep is depreceated, use nanosleep instead
        userInput();
        mapUpdate();
        draw();
        tc = time(NULL);
        dpf("    |||<%-11lld f pushed>|||    ",++fpush);
        setCursorPosition(60,26);
        dp("    +--------< DEBUG >---------+    ");
        setCursorPosition(60,28);
        dpf("    |||<%-12.3f avg fps>|||    ", ((float) fpush)/difftime(tc,tstart));
        // forceDraw();

    }

    return 0;
}
