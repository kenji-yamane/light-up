//
// Created by kenji on 17/09/22.
//

#include "Variable.h"

namespace modeling {

std::map<Domain, char> Variable::domainToAscii = std::map<Domain, char>{
    {Domain::EMPTY, ' '},
    {Domain::IMPOSSIBLE, 'X'},
    {Domain::LIGHT_BULB, 'L'},
    {Domain::UNDEFINED, '?'},
};

Variable::Variable(int line, int column) : line(line), column(column) {
    this->value = Domain::UNDEFINED;
}

char Variable::prettyDomain() const {
    return Variable::domainToAscii[this->value];
}

bool compareVariables(Variable a, Variable b) {
    return (a.restrictions > b.restrictions);
}

}
