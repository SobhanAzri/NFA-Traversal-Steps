//
// Created by nryxenon on 12/7/25.
//

#include "Automatas/state.h"
#include "Automatas/transition.h"

#define EPSILON '^'

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

std::vector<std::shared_ptr<State>> State::getDestinationStates(char symbol) const {
    std::vector<std::shared_ptr<State>> result;

    for (auto const& transition : transitions) {
        auto const &destinationStates = transition.second->getDestinationState();
        if (transition.second->hasSymbol(EPSILON))
        {
            result.push_back(destinationStates);
            for (auto const& states : destinationStates->getDestinationStates(symbol))
                result.push_back(states);
        }
        else if (transition.second->hasSymbol(symbol))
            result.push_back(transition.second->getDestinationState());
    }

    return result;
}
