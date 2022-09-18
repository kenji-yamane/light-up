//
// Created by kenji on 17/09/22.
//

#ifndef LIGHT_UP_AGENT_VARIABLE_H
#define LIGHT_UP_AGENT_VARIABLE_H

namespace modeling {

enum class Domain {
    LIGHT_BULB,
    EMPTY,
    UNDEFINED,
    IMPOSSIBLE
};

class Variable {
public:
    Variable();

    Domain value;
    int restrictionsCount;
};

}


#endif //LIGHT_UP_AGENT_VARIABLE_H
