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
    {Domain::WALL, '-'}
};

Variable::Variable() : restrictions(0), enlightened(false) {
    this->value = Domain::UNDEFINED;
}

char Variable::prettyDomain() const {
    return Variable::domainToAscii[this->value];
}

}
