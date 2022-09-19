//
// Created by kenji on 18/09/22.
//

#include "ConstraintSatisfaction.h"

#include <iostream>
#include <utility>

namespace decision_making {

ConstraintSatisfaction::ConstraintSatisfaction(modeling::Board initialBoard) :
    nodesVisited(0),
    initialBoard(std::move(initialBoard)) {
}

bool ConstraintSatisfaction::solve() {
    this->initialBoard.interpretRestrictions();
    if (not this->initialBoard.assertViability()) {
        return false;
    }
    auto undefinedVariables = this->initialBoard.degreeHeuristic();
    if (this->solve(State{undefinedVariables, this->initialBoard})) {
        return true;
    }
    return false;
}

bool ConstraintSatisfaction::solve(State s) {
    this->nodesVisited++;
    if (s.undefinedVariables.empty()) {
        this->solution = s.board;
        return true;
    }

    for (const auto &variable : s.undefinedVariables) {
        std::vector<State> children;
        if (s.board.assertLightBulb(variable.first, variable.second)) {
            children.push_back(decision_making::ConstraintSatisfaction::nextState(s, Light::ON, variable));
        }
        if (s.board.assertEmpty(variable.first, variable.second)) {
            children.push_back(decision_making::ConstraintSatisfaction::nextState(s, Light::OFF, variable));
        }
        for (const auto& next : children) {
            if (this->solve(next)) {
                return true;
            }
        }
    }
    return false;
}

State ConstraintSatisfaction::nextState(decision_making::State s, decision_making::Light l, std::pair<int, int> pos) {
    std::set<std::pair<int, int> > affectedVariables;
    switch (l) {
        case Light::ON:
            affectedVariables = s.board.lightUp(pos.first, pos.second);
            break;
        case Light::OFF:
            affectedVariables = s.board.lightDown(pos.first, pos.second);
            break;
    }
    auto it = s.undefinedVariables.begin();
    while (it != s.undefinedVariables.end()) {
        if (affectedVariables.find(std::pair(it->first, it->second)) != affectedVariables.end()) {
            auto aux = it;
            std::advance(it, 1);
            s.undefinedVariables.erase(aux);
        } else {
            std::advance(it, 1);
        }
    }
    return s;
}

}
