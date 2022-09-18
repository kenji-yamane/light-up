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
    int restrictionsCount;
    int line, column;

private:
    static std::map<Domain, char> domainToAscii;
};

bool compareVariables(Variable a, Variable b);

std::list<Variable>::iterator eraseVariable(
        std::list<Variable> &variables, std::list<Variable>::iterator it
);

}


#endif //LIGHT_UP_AGENT_VARIABLE_H
