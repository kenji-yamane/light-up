//
// Created by kenji on 17/09/22.
//

#ifndef LIGHT_UP_AGENT_RESTRICTION_H
#define LIGHT_UP_AGENT_RESTRICTION_H

#include <utility>
#include <vector>
#include <list>

#include "modeling/Variable.h"

namespace modeling {

class Restriction {
public:
    Restriction();
    explicit Restriction(int sum);

    [[nodiscard]] Domain interpret() const;

    [[nodiscard]] bool canAddLightBulbs() const;
    bool addLightBulb();
    [[nodiscard]] bool canAddEmpty() const;
    bool addEmpty();
    void addSquares(int num);

    [[nodiscard]] bool exists() const;
    [[nodiscard]] bool pending() const;

    [[nodiscard]] char prettyRestriction() const;

private:
    void checkIfSatisfied();

    int sum, lightBulbs, empties, squares;
    bool enabled, satisfied;
};

}


#endif //LIGHT_UP_AGENT_RESTRICTION_H
