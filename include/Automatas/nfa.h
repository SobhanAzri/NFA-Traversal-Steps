//
// Created by nryxenon on 12/7/25.
//

#ifndef NFA_TRAVERSAL_STEPS_NFA_H
#define NFA_TRAVERSAL_STEPS_NFA_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "state.h"

struct EvaluationResult; // forward decleration of the desired structure

class NFA {
public :
    NFA() = default;
    ~NFA() = default;

    void insertState(const std::string &name);

    void setInitialState(const std::string &stateName);
    void setFinalState(const std::string &stateName);

    State* getState(const std::string &stateName);
    [[nodiscard]] inline std::shared_ptr<State> getInitialState() const {return InitialState;};

    std::unordered_map<std::string, std::shared_ptr<State>> const& getAllStates() const { return states; }

    void initializeAlphabet(const char &symbol);
    std::vector<char> getAlphabet() const {return alphabet;}
    bool isSymbolInAlphabet(const char &symbol);

    void initializeTransitions(const std::string &currentState ,
                               const std::vector<std::string> &destinationStates,
                               const char &symbol);

    bool evaluateAutomata(const std::string &inputString);

    std::string getErrorsContext() const;

    void resetNFA();

protected:

   std::shared_ptr<State> InitialState;
   std::unordered_map<std::string, std::shared_ptr<State>> states;  // maybe i will change it from unique_ptr to shared_ptr later

   std::vector<char> alphabet;


   // Errors field
   bool m_bInitialStateError = false;
   bool m_bFinalStateError = false;
   bool m_bTransitionError = false;
};

#endif //NFA_TRAVERSAL_STEPS_NFA_H
