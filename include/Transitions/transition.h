//
// Created by nryxenon on 12/7/25.
//

#ifndef NFA_TRAVERSAL_STEPS_TRANSITION_H
#define NFA_TRAVERSAL_STEPS_TRANSITION_H

#include <vector>

class State;

class Transition {
public :
    Transition() = default;
    ~Transition() = default;

    void initTransition();

private :

    State* currentState;
    State* destinationState;

    std::vector<char> symbols;
};

#endif //NFA_TRAVERSAL_STEPS_TRANSITION_H
