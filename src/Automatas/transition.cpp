//
// Created by nryxenon on 12/7/25.
//

#include "Automatas/transition.h"

void Transition::initTransition() {

}

void Transition::setStates(const std::shared_ptr<State> &currentState, const std::shared_ptr<State> &destinationState) {
    this->currentState = currentState;
    this->destinationState = destinationState;

}


void Transition::addSymbols(const char &symbol) {
    symbols.push_back(symbol);
}



