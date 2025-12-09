//
// Created by nryxenon on 12/7/25.
//

#include <string>
#include <unordered_map>
#include <vector>

class State;

#ifndef NFA_TRAVERSAL_STEPS_NFA_H
#define NFA_TRAVERSAL_STEPS_NFA_H

class NFA {
public :
    NFA() = default;
    NFA(const std::string &filePath);
    ~NFA();

    void insertState(const std::string &name);

    void setInitialState(const std::string &stateName);

    State* getState(const std::string &stateName);
protected:
    std::string filePath;

   std::unique_ptr<State> InitialState;
   std::unordered_map<std::string, std::unique_ptr<State>> states;

    std::vector<char> alphabet;
};

#endif //NFA_TRAVERSAL_STEPS_NFA_H
