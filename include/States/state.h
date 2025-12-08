//
// Created by nryxenon on 12/7/25.
//

#ifndef NFA_TRAVERSAL_STEPS_STATE_H
#define NFA_TRAVERSAL_STEPS_STATE_H

#include <vector>

class Transition;

class State {
public :
    State() = default;
    ~State() = default;

protected :

    bool bIsInitialState = false;
    bool bIsFinalState = false;

    std::vector<Transition> transitions;
};

#endif //NFA_TRAVERSAL_STEPS_STATE_H
