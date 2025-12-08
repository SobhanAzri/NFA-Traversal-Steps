//
// Created by nryxenon on 12/7/25.
//

#include "Automatas/nfa.h"
#include "States/state.h"
#include "Transitions/transition.h"

NFA::NFA(const std::string &filePath) {
    this->filePath = filePath;
}

NFA::~NFA() {
    delete InitialState;
}

