#include <string>

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


char* filePath;
char* filePatterns[] = {"*.txt"};

void initializeMainWindow();

int main() {
    initializeMainWindow();

    NFA nfa;

    nfa.insertState("q0");
    nfa.insertState("q1");
    nfa.insertState("q2");

    nfa.initializeAlphabet('a');
    nfa.initializeAlphabet('b');

    nfa.setInitialState("q0");
    nfa.setFinalState("q2");

    std::vector<std::string> dest1 = {"q1"};
    std::vector<std::string> dest2 = {"q1", "q2"};

    nfa.initializeTransitions("q0", dest1, 'a');
    nfa.initializeTransitions("q0", dest2, 'b');


    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GRAY);

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









/*if (GuiButton(Rectangle{static_cast<int>(WINDOW_MAIN_WIDTH / 2 - 75),static_cast<int>(WINDOW_MAIN_HEIGHT / 2 - 15), 150 , 30},
                  GuiIconText(ICON_FILE_OPEN, "Open File...")))
        {
            filePath = tinyfd_openFileDialog(NULL,
                                             "~/"
                                             ,0,
                                             filePatterns,
                                             "Text Files",
                                             false);
        }

        GuiLabel(Rectangle{100,100, WINDOW_MAIN_WIDTH , 30},filePath);

        EndDrawing();
        */
