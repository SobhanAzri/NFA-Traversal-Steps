//
// Created by nryxenon on 12/7/25.
//

#ifndef NFA_TRAVERSAL_STEPS_NFA_H
#define NFA_TRAVERSAL_STEPS_NFA_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "States/state.h"


class NFA {
public :
    NFA() = default;
    explicit NFA(const std::string &filePath);
    ~NFA() = default;

    void insertState(const std::string &name);

    void setInitialState(const std::string &stateName);
    void setFinalState(const std::string &stateName);

    State* getState(const std::string &stateName);

    void initializeAlphabet(const char &symbol);
    void initializeTransitions(const std::string &currentState ,
                               const std::vector<std::string> &destinationStates,
                               const char &symbol);

protected:
    std::string filePath;

   std::shared_ptr<State> InitialState;
   std::unordered_map<std::string, std::shared_ptr<State>> states;  // maybe i will change it from unique_ptr to shared_ptr later

    std::vector<char> alphabet;
};

#endif //NFA_TRAVERSAL_STEPS_NFA_H
