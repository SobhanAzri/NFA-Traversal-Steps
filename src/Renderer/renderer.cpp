//
// Created by nryxenon on 12/11/25.
//

#include "Renderer/renderer.h"
#include "Automatas/nfa.h"
#include <cmath>

void Renderer::initializeVisualModel(const NFA &nfa) {

    auto *allStates = &nfa.getAllStates();
    stateCount = static_cast<int>(allStates->size());
    int iterator = 0;

    computePositions();

    // first loop for initializing State Properties
    for (auto &[name, statePointer] : *allStates)
    {
        StateProperties properties;
        properties.name = name;
        properties.bIsInitial = statePointer->isInitialState();
        properties.bIsFinal = statePointer->isFinalState();
        properties.radius = 100;
        properties.position = statePositions[iterator];

        iterator++;
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

    // computing grid for putting states


    // drawing states
    for (auto &[name, stateProperty] : visualStates)
    {
        DrawCircleLinesV(stateProperty.position,stateProperty.radius,BLACK);

        if (stateProperty.bIsFinal)
            DrawCircleLinesV(stateProperty.position,stateProperty.radius - 25,BLACK);

       DrawText(stateProperty.name.data(),stateProperty.position.x,stateProperty.position.y,30, BLACK);
    }

    // drawing transitions

    for (const auto &iterator : visualTransitions)
    {
        DrawLineV(visualStates[iterator.currentState].position,
                  visualStates[iterator.destinationState].position,
                  BLACK);
    }
}