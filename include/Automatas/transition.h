//
// Created by nryxenon on 12/7/25.
//

#ifndef NFA_TRAVERSAL_STEPS_TRANSITION_H
#define NFA_TRAVERSAL_STEPS_TRANSITION_H

#include <vector>
#include <memory>

class State;

class Transition {
public :
    Transition() = default;
    ~Transition() = default;

    void initTransition();

    void setStates(const std::shared_ptr<State> &currentState, const std::shared_ptr<State> &destinationState);
    void addSymbols(const char &symbol);

private :

    std::shared_ptr<State> currentState;
    std::shared_ptr<State> destinationState;

    std::vector<char> symbols;
};

#endif //NFA_TRAVERSAL_STEPS_TRANSITION_H
