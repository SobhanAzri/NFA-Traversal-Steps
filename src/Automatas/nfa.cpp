#include <memory>

#include "Automatas/nfa.h"
#include "Automatas/state.h"
#include "Automatas/transition.h"

NFA::NFA(const std::string &filePath) {
    this->filePath = filePath;
}

void NFA::insertState(const std::string &name) {
    states[name] = std::make_shared<State>();
    states[name]->setStateName(name);
}

void NFA::setInitialState(const std::string &stateName) {
    InitialState = states[stateName];
    InitialState->makeInitialState();
}

void NFA::setFinalState(const std::string &stateName) {
    states[stateName]->makeFinalState();
}

State* NFA::getState(const std::string &stateName) {
    auto desiredState = states.find(stateName);

    if (desiredState != states.end())
        return desiredState->second.get(); // come back later and check for the best method for returninh

    return nullptr;
}


void NFA::initializeAlphabet(const char &symbol) {
    alphabet.push_back(symbol);
}

void NFA::initializeTransitions(const std::string &currentState,
                                const std::vector<std::string> &destinationStates,
                                const char &symbol){
    auto currentStateIterator = states.find(currentState);

    for (const std::string &destination : destinationStates)
    {
        auto destinationStateIterator = states.find(destination);

        if (currentStateIterator != states.end() || destinationStateIterator != states.end())
            states[currentState]->initializeTransition(states[destination], symbol);
    }
}
