//
// Created by nryxenon on 12/7/25.
//

#include <string>
#include <vector>

class State;

#ifndef NFA_TRAVERSAL_STEPS_NFA_H
#define NFA_TRAVERSAL_STEPS_NFA_H

class NFA {
public :
    NFA() = default;
    NFA(const std::string &filePath);
    ~NFA();

protected:
    std::string filePath;

    State* InitialState;
    std::vector<State> normalStates;
    std::vector<State> finalStates;

    std::vector<char> alphabet;
};

#endif //NFA_TRAVERSAL_STEPS_NFA_H
