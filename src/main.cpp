#include <string>

#include "raylib.h"
#include "Tools/raygui.h"
#include "Automatas/nfa.h"
#include "Renderer/renderer.h"

extern "C"{
#include "Tools/tinyfiledialogs.h"
}

#define WINDOW_MAIN_TITLE "NFA Travers Steps"
#define WINDOW_MAIN_WIDTH 1920
#define WINDOW_AUTOMATA_WIDTH GetMonitorWidth(0)
#define WINDOW_MAIN_HEIGHT 1080
#define WINDOW_AUTOMATA_HEIGHT GetMonitorHeight(0)


char* filePath;
char* filePatterns[] = {"*.txt"};

void initializeMainWindow();

int main() {
    initializeMainWindow();

    NFA nfa;
    Renderer renderer;

    nfa.insertState("q0");
    nfa.insertState("q1");
    nfa.insertState("q2");
    nfa.insertState("q3");
//    nfa.insertState("q4");
//    nfa.insertState("q5");
//    nfa.insertState("q6");
//    nfa.insertState("q7");
//    nfa.insertState("q8");
//    nfa.insertState("q9");
//    nfa.insertState("q10");

    nfa.initializeAlphabet('a');
    nfa.initializeAlphabet('b');

    nfa.setInitialState("q0");
    nfa.setFinalState("q2");

    std::vector<std::string> dest1 = {"q1"};
    std::vector<std::string> dest2 = {"q1", "q2"};
    std::vector<std::string> dest3 = {"q3"};

    nfa.initializeTransitions("q0", dest1, 'a');
    nfa.initializeTransitions("q0", dest2, 'b');
    nfa.initializeTransitions("q0", dest3, '!');


    renderer.initializeVisualModel(nfa);


    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GRAY);

        renderer.drawVisualModel();

        EndDrawing();
    }


    CloseWindow();
    return 0;

}

void initializeMainWindow() {
    InitWindow(WINDOW_MAIN_WIDTH, WINDOW_MAIN_HEIGHT, WINDOW_MAIN_TITLE);
    SetTargetFPS(60);
    ToggleFullscreen();
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
