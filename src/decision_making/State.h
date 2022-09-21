//
// Created by kenji on 20/09/22.
//

#ifndef LIGHT_UP_AGENT_STATE_H
#define LIGHT_UP_AGENT_STATE_H

#include <list>
#include <utility>

#include "modeling/Board.h"

namespace decision_making {

struct State {
    std::list<std::pair<int, int> > undefinedVariables;
    modeling::Board board;
};

}

#endif //LIGHT_UP_AGENT_STATE_H
