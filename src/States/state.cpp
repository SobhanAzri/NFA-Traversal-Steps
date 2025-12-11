//
// Created by nryxenon on 12/7/25.
//

#include "States/state.h"
#include "Transitions/transition.h"

void State::initializeTransition(std::shared_ptr<State> destinationState, const char &symbol) {
    const std::string &destinationName = destinationState->getStateName();
    auto iterator = transitions.find(destinationName);

    if (iterator != transitions.end())
        iterator->second->addSymbols(symbol);
    else
    {
        auto transition = std::make_shared<Transition>();

        transition->setStates(getClassPtr(),destinationState);
        transition->addSymbols(symbol);

        transitions.insert({destinationName, transition});
    }
}
