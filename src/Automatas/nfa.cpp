#include <memory>

#include "Automatas/nfa.h"
#include "Automatas/state.h"
#include "Automatas/evaluator.h"

#define EPSILON '^'

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

bool NFA::evaluateAutomata(const std::string &inputString) {

    const int inputSize = static_cast<int>(inputString.size());
    char symbol = inputString[0];
    int stringIterator = 0;
    bool canIterateString = true;

    EvaluationResult result;

    std::vector<std::shared_ptr<State>> currentStates;
    currentStates.push_back(InitialState);

    result.steps.push_back({'!',{getInitialState()->getStateName()}}); // adding initial state without a symbol

    if (symbol == '\0')
        symbol = EPSILON;

    while (canIterateString) {


        if (symbol != EPSILON)
            symbol = inputString[stringIterator];

        if (symbol == '\0')
            symbol = EPSILON;

        std::vector<std::shared_ptr<State>> nextStates;

        for (auto &state : currentStates) {
            auto statesHolder = state->getDestinationStates(symbol);
            nextStates.insert(nextStates.end(), statesHolder.begin(), statesHolder.end());
        }

        if (nextStates.empty())
            return false;

        currentStates = nextStates;


        stringIterator++;
        if (stringIterator >= inputSize)
            canIterateString = false;
    }

    // for (auto symbol : inputString) {
    //     std::vector<std::shared_ptr<State>> nextStates;
    //
    //     for (auto &state : currentStates) {
    //         auto destinations = state->getDestinationStates(symbol);
    //
    //         nextStates.insert(nextStates.end(), destinations.begin(), destinations.end());
    //     }
    //
    //     if (nextStates.empty())
    //         return false;
    //
    //     currentStates = nextStates;
    //
    //     TraversalStep step;
    //     step.symbol = symbol;
    //
    //     for (auto &state : currentStates)
    //         step.states.push_back(state->getStateName());
    //
    //     result.steps.push_back(step);
    // }

    for (auto &state : currentStates)
        if (state->isFinalState()) {
            return true;
        }

    return false;
}