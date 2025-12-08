#include "raylib.h"
#include "Tools/raygui.h"
#include "Automatas/nfa.h"

extern "C"{
#include "Tools/tinyfiledialogs.h"
}

#define WINDOW_MAIN_TITLE "NFA Travers Steps"
#define WINDOW_MAIN_WIDTH 900
#define WINDOW_AUTOMATA_WIDTH GetMonitorWidth(0)
#define WINDOW_MAIN_HEIGHT 600
#define WINDOW_AUTOMATA_HEIGHT GetMonitorHeight(0)

void initializeMainWindow();

int main() {
    initializeMainWindow();

    NFA nfa;

    while (!WindowShouldClose()) {
        BeginDrawing();

        EndDrawing();
    }


    CloseWindow();
    return 0;

}

void initializeMainWindow() {
    InitWindow(WINDOW_MAIN_WIDTH, WINDOW_MAIN_HEIGHT, WINDOW_MAIN_TITLE);
    SetTargetFPS(60);
    ClearBackground(LIGHTGRAY);
}
