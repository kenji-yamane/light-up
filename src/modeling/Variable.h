//
// Created by kenji on 17/09/22.
//

#ifndef LIGHT_UP_AGENT_VARIABLE_H
#define LIGHT_UP_AGENT_VARIABLE_H

#include <map>
#include <list>

namespace modeling {

enum class Domain {
    LIGHT_BULB,
    EMPTY,
    UNDEFINED,
    IMPOSSIBLE
};

class Variable {
public:
    Variable(int line, int column);

    [[nodiscard]] char prettyDomain() const;

    Domain value;
    int restrictions;
    int line, column;

private:
    static std::map<Domain, char> domainToAscii;
};

bool compareVariables(Variable a, Variable b);

}


#endif //LIGHT_UP_AGENT_VARIABLE_H
