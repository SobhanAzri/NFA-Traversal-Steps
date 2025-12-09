//
// Created by nryxenon on 12/7/25.
//

#ifndef NFA_TRAVERSAL_STEPS_STATE_H
#define NFA_TRAVERSAL_STEPS_STATE_H

#include <string>
#include <vector>

class Transition;

class State {
public :
    State() = default;
    ~State() = default;

    inline void setStateName(const std::string &name) { stateName = name;}
    [[nodiscard]] inline std::string getStateName() const { return stateName;}

    inline void makeInitialState() {bIsInitialState = true};

protected :

    bool bIsInitialState = false;
    bool bIsFinalState = false;

    std::string stateName;

    std::vector<Transition> transitions;
};

#endif //NFA_TRAVERSAL_STEPS_STATE_H
