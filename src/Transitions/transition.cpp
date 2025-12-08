//
// Created by nryxenon on 12/7/25.
//

#include "Transitions/transition.h"
#include "States/state.h"

void Transition::initTransition() {

}

void Transition::setStates(State* currentState, State* destinationState) {
    this->currentState = currentState;
    this->destinationState = destinationState;
}

void Transition::setSymbols(const char *symbol) {

}
