//
// Created by kenji on 17/09/22.
//

#include "Restriction.h"

namespace modeling {

Restriction::Restriction() : sum(0), lightBulbs(0), empties(0), squares(0), enabled(false), satisfied(false) {}

Restriction::Restriction(int sum) : sum(sum), lightBulbs(0), empties(0), squares(0), enabled(true), satisfied(false) {}

Domain Restriction::interpret() const {
    if (this->sum == 0) {
        return Domain::EMPTY;
    }
    if (this->sum > (int)this->squares) {
        return Domain::IMPOSSIBLE;
    }
    if (this->sum == (int)this->squares) {
        return Domain::LIGHT_BULB;
    }
    return Domain::UNDEFINED;
}

bool Restriction::canAddLightBulbs() const {
    if (not this->enabled) {
        return true;
    }
    return (this->lightBulbs < this->sum);
}

bool Restriction::addLightBulb() {
    if (not this->enabled) {
        return true;
    }
    if (not this->canAddLightBulbs()) {
        return false;
    }
    this->lightBulbs++;
    this->checkIfSatisfied();
    return true;
}

bool Restriction::canAddEmpty() const {
    if (not this->enabled) {
        return true;
    }
    return ((int)this->squares - this->empties > this->sum);
}

bool Restriction::addEmpty() {
    if (not this->enabled) {
        return true;
    }
    if (not this->canAddEmpty()) {
        return false;
    }
    this->empties++;
    this->checkIfSatisfied();
    return true;
}

void Restriction::addSquares(int num) {
    this->squares += num;
}

bool Restriction::exists() const {
    return this->enabled;
}

bool Restriction::pending() const {
    return (this->enabled and not this->satisfied);
}

char Restriction::prettyRestriction() const {
    return (char)(this->sum + '0');
}

void Restriction::checkIfSatisfied() {
    if (this->sum == 0) {
        this->satisfied = (this->squares == this->empties);
    } else {
        this->satisfied = (this->sum == this->lightBulbs);
    }
}

}
