//
// Created by nryxenon on 12/7/25.
//

#ifndef NFA_TRAVERSAL_STEPS_STATE_H
#define NFA_TRAVERSAL_STEPS_STATE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Transitions/transition.h"


class State:  public std::enable_shared_from_this<State>{
public :
    State() = default;
    ~State() = default;

    inline void setStateName(const std::string &name) { stateName = name;}
    [[nodiscard]] inline std::string getStateName() const { return stateName;}

    inline void makeInitialState() {bIsInitialState = true;}
    inline void makeFinalState() {bIsFinalState = true;}

    void initializeTransition(std::shared_ptr<State> destinationState, const char &symbol);

    inline std::shared_ptr<State> getClassPtr() { return shared_from_this(); }

protected :

    bool bIsInitialState = false;
    bool bIsFinalState = false;

    std::string stateName;

    std::unordered_map<std::string , std::shared_ptr<Transition>> transitions; // the string key is for the name of destionation state
};

#endif //NFA_TRAVERSAL_STEPS_STATE_H
