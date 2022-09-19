//
// Created by kenji on 17/09/22.
//

#include "Restriction.h"
#include <iostream>

namespace modeling {

Restriction::Restriction(int sum) : sum(sum), lightBulbs(0), empties(0) {}

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

bool Restriction::canAddLightBulbs() const {
    return (this->lightBulbs < this->sum);
}

bool Restriction::addLightBulb() {
    if (not this->canAddLightBulbs()) {
        return false;
    }
    this->lightBulbs++;
    return true;
}

bool Restriction::canAddEmpty() const {
    return ((int)this->squares.size() - this->empties > this->sum);
}

bool Restriction::addEmpty() {
    if (not this->canAddEmpty()) {
        return false;
    }
    this->empties++;
    return true;
}

}
