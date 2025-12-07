//
// Created by nryxenon on 12/7/25.
//

#include <vector>

class State;

#ifndef NFA_TRAVERSAL_STEPS_NFA_H
#define NFA_TRAVERSAL_STEPS_NFA_H

class NFA {
public :
    NFA() = default;
    ~NFA() = default;

protected:
    State* InitialState;
    std::vector<State> normalStates;
    std::vector<State> finalStates;
};

#endif //NFA_TRAVERSAL_STEPS_NFA_H
