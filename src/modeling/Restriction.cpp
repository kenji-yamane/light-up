//
// Created by kenji on 17/09/22.
//

#include "Restriction.h"

namespace modeling {

Restriction::Restriction(int sum) : sum(sum) {}

void Restriction::addSquare(int line, int column) {
    this->squares.emplace_back(line, column);
}

Domain Restriction::interpret() const {
    if (this->sum == 0) {
        return Domain::EMPTY;
    }
    if (this->sum > (int)this->squares.size()) {
        return Domain::IMPOSSIBLE;
    }
    if (this->sum == (int)this->squares.size()) {
        return Domain::LIGHT_BULB;
    }
    return Domain::UNDEFINED;
}

}
