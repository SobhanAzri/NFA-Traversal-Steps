
//
// Created by nryxenon on 12/7/25.
//

#include "Automatas/state.h"
#include "Automatas/transition.h"
#include <iterator>
#include <memory>
#include "Tools/constants.h"

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

    auto self = getClassPtr();

    if (states.contains(self))
        return;

    states.insert(self);

    for (auto const &transition : transitions){
        if (transition.second->hasSymbol(NFA_EPSILON)) {
            transition.second->getDestinationState()->epsilonClosure(states);
        }
    }
}

void State::clear() {
    bIsInitialState = false;
    bIsFinalState = false;
    stateName.clear();

    for (auto transition : transitions)
    {
        transition.second->clear();
        transition.second = nullptr;
    }

    transitions.clear();
}
