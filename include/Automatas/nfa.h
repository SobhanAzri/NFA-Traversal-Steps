//
// Created by nryxenon on 12/7/25.
//

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "States/state.h"

#ifndef NFA_TRAVERSAL_STEPS_NFA_H
#define NFA_TRAVERSAL_STEPS_NFA_H

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

protected:
    std::string filePath;

   std::unique_ptr<State> InitialState;
   std::unordered_map<std::string, std::unique_ptr<State>> states;

    std::vector<char> alphabet;
};

#endif //NFA_TRAVERSAL_STEPS_NFA_H
