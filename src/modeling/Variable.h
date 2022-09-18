//
// Created by kenji on 17/09/22.
//

#ifndef LIGHT_UP_AGENT_VARIABLE_H
#define LIGHT_UP_AGENT_VARIABLE_H

#include <map>

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
    char prettyDomain() const;

    Domain value;
    int restrictionsCount;

private:
    static std::map<Domain, char> domainToAscii;
};

}


#endif //LIGHT_UP_AGENT_VARIABLE_H
