//
// Created by kenji on 17/09/22.
//

#include "Restriction.h"

namespace modeling {

Restriction::Restriction() : squares(), sum(0), lightBulbs(0), empties(0), enabled(false), satisfied(false) {}

Restriction::Restriction(int sum) : squares(), sum(sum), lightBulbs(0), empties(0), enabled(true), satisfied(false) {}

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
    return true;
}

bool Restriction::canAddEmpty() const {
    if (not this->enabled) {
        return true;
    }
    return ((int)this->squares.size() - this->empties > this->sum);
}

bool Restriction::addEmpty() {
    if (not this->enabled) {
        return true;
    }
    if (not this->canAddEmpty()) {
        return false;
    }
    this->empties++;
    return true;
}

char Restriction::prettyRestriction() const {
    return (char)(this->sum + '0');
}

bool Restriction::exists() const {
    return this->enabled;
}

void Restriction::satisfy() {
    this->satisfied = true;
}

bool Restriction::pending() const {
    return (this->enabled and not this->satisfied);
}

}
