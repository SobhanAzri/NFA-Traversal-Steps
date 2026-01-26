//
// Created by nryxenon on 12/22/25.
//

#ifndef NFA_TRAVERSAL_STEPS_EVALUATOR_H
#define NFA_TRAVERSAL_STEPS_EVALUATOR_H
#include <vector>
#include <string>

struct TraversalStep {
    char symbol;
    std::vector<std::string> states;
};

struct EvaluationResult {
  bool isAccepted = false;
  std::vector<TraversalStep> steps;
};

#endif //NFA_TRAVERSAL_STEPS_EVALUATOR_H
