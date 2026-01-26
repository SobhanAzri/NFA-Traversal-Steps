

/*
 *
 *          At the start of this project i didnt have that much of experience in Game Loop Structures and Design Patterns
 *          so this main.cpp is a bit messier than it should be.
 *
 */



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

#define FILE_PATH "Automata.txt"

Font font;

char* filePath;
char* filePatterns[] = {"*.txt"};
std::vector<int> codepoints;
char* errorsContext;

bool isRunning = true;
bool requestOpenFile = false;

void initializeMainWindow();
void initializeTextField(char userInput[], bool &canEdit);
void initializeQuitButton();

int main() {
    initializeMainWindow();

    // initializing codepoints for adding support for lambda and sigma symbols
    for (int i = 32; i < 127; i++)
        codepoints.push_back(i);
    codepoints.push_back(0x03BB);
    codepoints.push_back(0x03A3);

    font = LoadFontEx("resources/font.ttf", 64, codepoints.data(), codepoints.size());
    Renderer::getInstance().initializeFont(font);

    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);

    char inputString[] = "";
    bool stringAccepted = false;
    bool showStringState = false;
    bool editMode = false;

    NFA nfa;
    FileLoader::loadNfa(nfa,FILE_PATH);
    Renderer::getInstance().initializeVisualModel(nfa);


    while (!WindowShouldClose() && isRunning) {
       /*  if (requestOpenFile)
        {
            filePath = tinyfd_openFileDialog("Open File", ".", 0, filePatterns, "Text Files", 0);

            if (filePath)
            {
                Renderer::getInstance().resetRenderer();
                nfa.resetNFA();

                FileLoader::loadNfa(nfa,filePath);
                Renderer::getInstance().initializeVisualModel(nfa);
            }

            requestOpenFile = false;
            continue;
        }*/

        BeginDrawing();
        ClearBackground(WHITE);

        Renderer::getInstance().drawVisualModel();

        // file loader button
        if (GuiButton({25, static_cast<float>(WINDOW_AUTOMATA_HEIGHT - 35), 475 , 30},
            "Reload Automata.txt"))
        {
            Renderer::getInstance().resetRenderer();
            nfa.resetNFA();

            FileLoader::loadNfa(nfa,FILE_PATH);
            Renderer::getInstance().initializeVisualModel(nfa);
        }

        // String Checker
        if (GuiButton({400,1000,100,40},"CHECK")) {

                showStringState = true;
                stringAccepted = nfa.evaluateAutomata(inputString);
        }

        if (showStringState) {
            if (stringAccepted)
                DrawTextEx(font, "YES, this automata accepts this string!", {550 , 1025}, 32, 1, GREEN);
            else
                DrawTextEx(font, "NO, this string is not accepted by this automata!", {550 , 1025}, 32, 1, RED);
        }

        initializeTextField(inputString, editMode);
        initializeQuitButton();

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
    GuiLoadStyle("resources/style.rgs");
    ClearBackground(LIGHTGRAY);
}

void initializeTextField(char userInput[], bool &canEdit) {
    Rectangle rect = {25, static_cast<float>(WINDOW_AUTOMATA_HEIGHT - 80), 350, 40,};

    if (GuiTextBox(rect, userInput, 64, canEdit))
        canEdit = !canEdit;
}

void initializeQuitButton() {
    if (GuiButton({static_cast<float>(WINDOW_AUTOMATA_WIDTH - 55), 5, 50 , 50}, "X")) {
        isRunning = false;
    }
}
