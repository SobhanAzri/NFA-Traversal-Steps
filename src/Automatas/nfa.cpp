#include <memory>

#include "Automatas/nfa.h"
#include "States/state.h"
#include "Transitions/transition.h"

NFA::NFA(const std::string &filePath) {
    this->filePath = filePath;
}

void NFA::insertState(const std::string &name) {
    states[name] = std::make_unique<State>();
    states[name]->setStateName(name);
}

void NFA::setInitialState(const std::string &stateName) {
    InitialState = std::move(states[stateName]);
    InitialState->makeInitialState();
}

State* NFA::getState(const std::string &stateName) {
    auto desiredState = states.find(stateName);

    if (desiredState != states.end())
        return desiredState->second.get(); // come back later and check for the best method for returninh

    return nullptr;
}

void NFA::setFinalState(const std::string &stateName) {
    states[stateName]->makeFinalState();
}

void NFA::initializeAlphabet(const char &symbol) {
    alphabet.push_back(symbol);
}
