//
// Created by nryxenon on 12/11/25.
//

#ifndef NFA_TRAVERSAL_STEPS_RENDERER_H
#define NFA_TRAVERSAL_STEPS_RENDERER_H

#include <memory>
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

    Renderer() = default;

public :

    Renderer(Font font) : font(font) {}
    ~Renderer()= default;

    static Renderer& getInstance();

    inline void initializeFont(Font font) { this->font = font; }

    void initializeVisualModel(const NFA &nfa);

    void computePositions();

    void drawVisualModel();

    void resetRenderer();

protected :

    int stateCount = 0;
    std::vector<char> alphabet;

    std::unordered_map<std::string ,StateProperties> visualStates;
    std::vector<TransitionProperties> visualTransitions;

    std::vector<Vector2> statePositions;

    Font font;
    std::string errorsContext;

private :
    static std::unique_ptr<Renderer> s_pInstance;

};
#endif //NFA_TRAVERSAL_STEPS_RENDERER_H
