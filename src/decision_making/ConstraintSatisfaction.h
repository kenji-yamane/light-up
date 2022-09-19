//
// Created by kenji on 18/09/22.
//

#ifndef LIGHT_UP_AGENT_CONSTRAINTSATISFACTION_H
#define LIGHT_UP_AGENT_CONSTRAINTSATISFACTION_H

#include "modeling/Board.h"

namespace decision_making {

enum class Light {
    ON,
    OFF
};

struct State {
    std::list<std::pair<int, int> > undefinedVariables;
    modeling::Board board;
};

class ConstraintSatisfaction {
public:
    explicit ConstraintSatisfaction(modeling::Board initialBoard);
    bool solve();

    modeling::Board solution;
    int nodesVisited;

private:
    bool solve(State s);
    static State nextState(State s, Light l, std::pair<int, int> pos);

    modeling::Board initialBoard;
};

}


#endif //LIGHT_UP_AGENT_CONSTRAINTSATISFACTION_H
