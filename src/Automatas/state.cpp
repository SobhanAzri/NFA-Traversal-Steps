//
// Created by nryxenon on 12/7/25.
//

#include "Automatas/state.h"
#include "Automatas/transition.h"
#include <memory>

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
        if (transition.second->hasSymbol(symbol))
            result.push_back(transition.second->getDestinationState());
    }

    return result;
}

void State::epsilonClosure(std::unordered_set<std::shared_ptr<State>> &states) {

    if (states.contains(getClassPtr()))
        return;

    states.insert(shared_from_this());

    for (auto const &transition : transitions){
        if (transition.second->hasSymbol(EPSILON)) {
            transition.second->getDestinationState()->epsilonClosure(states);
        }
    }
}

void State::clear() {
    bool bIsInitialState = false;
    bool bIsFinalState = false;
    stateName.clear();

    for (auto transition : transitions)
    {
        transition.second->clear();
        transition.second = nullptr;
    }

    transitions.clear();
}
