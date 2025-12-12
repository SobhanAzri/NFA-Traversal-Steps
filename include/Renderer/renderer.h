//
// Created by nryxenon on 12/11/25.
//

#ifndef NFA_TRAVERSAL_STEPS_RENDERER_H
#define NFA_TRAVERSAL_STEPS_RENDERER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "raylib.h"

class NFA;

struct StateProperties {
    std::string name;
    Vector2 position;
    float radius;
    bool bIsInitial;
    bool bIsFinal;
};

struct TransitionProperties {
    std::string currentState;
    std::string destinationState;
    std::vector<char> symbols;
};

class Renderer {
public :
    Renderer() = default;
    ~Renderer() = default;

    void initializeVisualModel(const NFA &nfa);

    static float computeRadius();
    void computePositions();

    void drawVisualModel();

protected :
    int stateCount;

    std::unordered_map<std::string ,StateProperties> visualStates;
    std::vector<TransitionProperties> visualTransitions;

    std::vector<Vector2> statePositions;
};
#endif //NFA_TRAVERSAL_STEPS_RENDERER_H
