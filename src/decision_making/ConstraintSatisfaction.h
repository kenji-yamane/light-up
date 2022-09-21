//
// Created by kenji on 18/09/22.
//

#ifndef LIGHT_UP_AGENT_CONSTRAINTSATISFACTION_H
#define LIGHT_UP_AGENT_CONSTRAINTSATISFACTION_H

#include "decision_making/State.h"

namespace decision_making {

class ConstraintSatisfaction {
public:
    explicit ConstraintSatisfaction(modeling::Board initialBoard);
    bool solve();

    modeling::Board solution;
    int nodesVisited;

private:
    bool solve(const State& s);

    modeling::Board initialBoard;
};

}


#endif //LIGHT_UP_AGENT_CONSTRAINTSATISFACTION_H
