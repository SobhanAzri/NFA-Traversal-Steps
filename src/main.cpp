#include <string>
#include "raylib.h"
#include "Automatas/nfa.h"
#include "Renderer/renderer.h"
#include "Tools/tinyfiledialogs.h"
#include "Tools/fileLoader.h"

#define RAYGUI_IMPLEMENTATION
#include "Tools/raygui.h"

#define WINDOW_MAIN_TITLE "NFA Travers Steps"
#define WINDOW_MAIN_WIDTH 1920
#define WINDOW_AUTOMATA_WIDTH GetMonitorWidth(0)
#define WINDOW_MAIN_HEIGHT 1080
#define WINDOW_AUTOMATA_HEIGHT GetMonitorHeight(0)

char* filePath;
char* filePatterns[] = {"*.txt"};
std::vector<int> codepoints;

void initializeMainWindow();
void initializeTextField(char userInput[], bool &canEdit);

int main() {
    initializeMainWindow();

    // initializing codepoints for adding support for lambda and sigma symbols
    for (int i = 32; i < 127; i++)
        codepoints.push_back(i);
    codepoints.push_back(0x03BB);
    codepoints.push_back(0x03A3);

    Font font = LoadFontEx("resources/Roboto.ttf", 64, codepoints.data(), codepoints.size());

    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

    char inputString[] = "";
    bool stringAccepted = false;
    bool showStringState = false;
    bool editMode = false;

    NFA nfa;
    Renderer renderer(font);

    FileLoader::loadNfa(nfa,"");

    // nfa.insertState("q0");
    // nfa.insertState("q1");
    // nfa.insertState("q2");
    // nfa.insertState("q3");
    // nfa.insertState("q4");
    // nfa.insertState("q5");
    // nfa.insertState("q6");
    // nfa.insertState("q7");
    // nfa.insertState("q8");
    // nfa.insertState("q9");
    // nfa.insertState("q10");
    //
    // nfa.initializeAlphabet('a');
    // nfa.initializeAlphabet('b');
    //
    // nfa.setInitialState("q0");
    // nfa.setFinalState("q0");
    // nfa.setFinalState("q2");
    //
    // std::vector<std::string> dest0 = {"q0"};
    // std::vector<std::string> dest1 = {"q1"};
    // std::vector<std::string> dest2 = { "q2"};
    // std::vector<std::string> dest3 = {"q3"};
    //
    // nfa.initializeTransitions("q1", dest0, 'a');
    // nfa.initializeTransitions("q0", dest2, 'b');
    // nfa.initializeTransitions("q0", dest3, 'a');
    // nfa.initializeTransitions("q3", dest1, 'a');


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        renderer.drawVisualModel();


        // String Checker
        if (GuiButton({400,1000,100,40},"CHECK")) {
            // if string is empty and our initial state is final then dont calculate anything

                showStringState = true;
                stringAccepted = nfa.evaluateAutomata(inputString);
        }

        if (showStringState) {
            if (stringAccepted)
                DrawTextEx(font, "YES, this automata accepts this string!", {550 , 1025}, 32, 1, GREEN);
            else
                DrawTextEx(font, "NO, this string is not accepted by this automata!", {550 , 1025}, 32, 1, RED);
        }



        // file loader button

        if (GuiButton({25, static_cast<float>(WINDOW_AUTOMATA_HEIGHT - 35), 475 , 30},
            "Load NFA From a File"))
        {
            filePath = tinyfd_openFileDialog(
            "Select file",
            ".",
            0,
            filePatterns,
           "Text Files",
           0);

            FileLoader::loadNfa(nfa,filePath);
            renderer.initializeVisualModel(nfa);
        }

        initializeTextField(inputString, editMode);

        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
    return 0;

}

void initializeMainWindow() {
    InitWindow(WINDOW_MAIN_WIDTH, WINDOW_MAIN_HEIGHT, WINDOW_MAIN_TITLE);
    SetTargetFPS(30);
    ToggleFullscreen();
    ClearBackground(LIGHTGRAY);
}

void initializeTextField(char userInput[], bool &canEdit) {
    Rectangle rect = {25,
                    static_cast<float>(WINDOW_AUTOMATA_HEIGHT - 80),
                        350, 40,};

    if (GuiTextBox(rect, userInput, 64, canEdit))
        canEdit = !canEdit;
}
