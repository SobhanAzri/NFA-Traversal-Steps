//
// Created by nryxenon on 12/11/25.
//

#ifndef NFA_TRAVERSAL_STEPS_RENDERER_H
#define NFA_TRAVERSAL_STEPS_RENDERER_H

#include <string>
#include <vector>
#include "raylib.h"

struct StateProperties {
    std::string name;
    Vector2 position;
    bool bIsInitial;
    bool bIsFinal;
};

struct TransitionProperties {
    std::string currentState;
    std::string destinationState;
    std::vector<char> symbols;
};
#endif //NFA_TRAVERSAL_STEPS_RENDERER_H
