//
// Created by nryxenon on 12/11/25.
//

#include "Renderer/renderer.h"
#include "Automatas/nfa.h"
#include "Tools/raygui.h"

#define RADIUS 80
#define EPSILON '^'
int codepoints[] = { 0x03BB, 0x03C3 };

void drawArrow(const Vector2 &start, const Vector2 &end)
{
    // adding the state circles offset radius to the end



    float dx = (end.x - start.x);
    float dy = (end.y - start.y);

    float angle = atan2f(dy, dx);

    Vector2 left = {
            end.x - 20 * cosf(angle - .5f),
            end.y - 20 * sinf(angle - .5)
    };

    Vector2 right = {
            end.x - 20 * cosf(angle + .5f),
            end.y - 20 * sinf(angle + .5)
    };

    DrawLineEx(start, end, 2, BLACK);
    DrawLineEx(end, left, 2,BLACK);
    DrawLineEx(end, right, 2,BLACK);
}

void Renderer::initializeVisualModel(const NFA &nfa) {

    auto *allStates = &nfa.getAllStates();
    stateCount = static_cast<int>(allStates->size());
    int iterator = stateCount - 1;

    computePositions();

    // first Initialize Alphabet
    alphabet = nfa.getAlphabet();

    // first loop for initializing State Properties
    for (auto &[name, statePointer] : *allStates)
    {
        StateProperties properties;
        properties.name = name;
        properties.bIsInitial = statePointer->isInitialState();
        properties.bIsFinal = statePointer->isFinalState();
        properties.radius = RADIUS;
        properties.position = statePositions[iterator];

        iterator--;
        visualStates[name] = properties;
    }

    // second loop for initializing Transition properties
    for (auto &[name, statePointer] : nfa.getAllStates())
    {
        for (auto &[destinationName , transitionPointer] : statePointer->getAllTransitions())
        {
            TransitionProperties properties;
            properties.currentState = statePointer->getStateName();
            properties.destinationState = destinationName;
            properties.symbols = transitionPointer->getSymbols();

            visualTransitions.push_back(properties);
        }
    }
}

float Renderer::computeRadius() {
    return 0;
}

void Renderer::computePositions() {
    statePositions.clear();

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int columns = ceil(sqrt(stateCount));
    int rows = ceil((float)stateCount / columns);

    float cellWidth = (float)screenWidth / columns;
    float cellHeight = (float)screenHeight / rows;

    for (int i = 0; i < stateCount; i++)
    {
        int r = i / columns;
        int c = i % columns;

        float x = c * cellWidth + cellWidth / 2.0f;
        float y = r * cellHeight + cellHeight / 2.0f;

        statePositions.push_back({x, y});
    }
}

void Renderer::drawVisualModel() {


    Font font = LoadFont("resources/DejaVuSans.ttf");

    // drawing Alphabet
    std::string alphabetText = "Alphabet = { ";
    for (auto const &symbol : alphabet) {
        alphabetText += symbol;
        alphabetText += " , ";
    }
    alphabetText.replace(alphabetText.length() - 2,1,"}");

    DrawTextEx(font, alphabetText.data(), {12,12}, 32, 1, BLACK);


    // drawing states
    for (auto &[name, stateProperty] : visualStates)
    {
        DrawCircleLinesV(stateProperty.position,stateProperty.radius,BLACK);

        if (stateProperty.bIsFinal)
            DrawCircleLinesV(stateProperty.position,(stateProperty.radius * .8f),BLACK);

       DrawTextEx(font,stateProperty.name.data(),
           {stateProperty.position.x,stateProperty.position.y},
           32,1, BLACK);

    }

    // drawing transitions

    for (const auto &iterator : visualTransitions)
    {
        drawArrow(visualStates[iterator.currentState].position,
                  visualStates[iterator.destinationState].position);


        std::string symbols = "{ ";
        for (auto const character : iterator.symbols) {

            if (character == EPSILON)
                symbols += "λ";
            else
                symbols += character;
            symbols += ",";
        }
        symbols.replace(symbols.length() - 1,1," }");

        // drawing symbols of a transition
        DrawTextEx(font, symbols.data(),
                 {(visualStates[iterator.currentState].position.x + visualStates[iterator.destinationState].position.x) /2 + 5,
                 (visualStates[iterator.currentState].position.y + visualStates[iterator.destinationState].position.y) /2 + 5},
                 32, 1, BLACK);
    }
}