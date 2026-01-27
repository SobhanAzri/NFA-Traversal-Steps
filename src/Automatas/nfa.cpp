#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <raymath.h>
#include <unordered_set>

#include "Automatas/nfa.h"
#include "Automatas/state.h"
#include "Tools/constants.h"

void NFA::insertState(const std::string &name) {
    states[name] = std::make_shared<State>();
    states[name]->setStateName(name);
}

void NFA::setInitialState(const std::string &stateName) {
    auto tempState = states.find(stateName);

    if (tempState != states.end()){
        InitialState = states[stateName];
        InitialState->makeInitialState();
    }
    else
        m_bInitialStateError = true;
}

void NFA::setFinalState(const std::string &stateName) {
    auto tempState = states.find(stateName);

    if (tempState != states.end())
        states[stateName]->makeFinalState();
    else
        m_bFinalStateError = true;
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

bool NFA::isSymbolInAlphabet(const char &symbol) {

    for (auto character : alphabet) {
        if(symbol == character)
            return true;
    }

    return false;
}

void NFA::initializeTransitions(const std::string &currentState,
                                const std::vector<std::string> &destinationStates,
                                const char &symbol){
    auto currentStateIterator = states.find(currentState);

    for (const std::string &destination : destinationStates)
    {
        auto destinationStateIterator = states.find(destination);

        if (currentStateIterator != states.end() && destinationStateIterator != states.end() && (isSymbolInAlphabet(symbol) || symbol == NFA_EPSILON))
            states[currentState]->initializeTransition(states[destination], symbol);
        else {
            m_bTransitionError = true;
            return;
        }
    }
}

bool NFA::evaluateAutomata(const std::string &inputString) {


    std::unordered_set<std::shared_ptr<State>> currentStates;

    InitialState->epsilonClosure(currentStates);


    for ( auto const symbol : inputString ) {

        if (!isSymbolInAlphabet(symbol))
            return false;

        std::unordered_set<std::shared_ptr<State>> nextStates;

        for (auto state : currentStates) {
            for (auto destination : state->getDestinationStates(symbol)) {
                destination->epsilonClosure(nextStates);
            }
        }

        if (nextStates.empty()){
            m_bInitialStateError = true;
            return false;
        }

        currentStates = std::move(nextStates);
    }


    for (auto &state : currentStates)
        if (state->isFinalState()) {
            return true;
        }

    return false;
}

std::string NFA::getErrorsContext() const {

    std::string errorsContext = "";

    if (m_bInitialStateError)
        errorsContext += "Start state field of your nfa has a problem !\n\n";

    if (m_bFinalStateError)
        errorsContext += "Final states field of your nfa has a problem !\n\n";

    if (m_bTransitionError)
        errorsContext += "Transitions field of your nfa has a problem !";

    return errorsContext;
}

void NFA::resetNFA() {

    alphabet.clear();


    for (auto state : states) {
        state.second->clear();
        state.second = nullptr;
    }

    InitialState = nullptr;
    states.clear();

    m_bInitialStateError = false;
    m_bFinalStateError = false;
    m_bTransitionError = false;
}
