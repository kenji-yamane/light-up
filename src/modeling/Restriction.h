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
    void addSquares(int num);
    [[nodiscard]] Domain interpret() const;
    [[nodiscard]] bool canAddLightBulbs() const;
    bool addLightBulb();
    [[nodiscard]] bool canAddEmpty() const;
    bool addEmpty();
    [[nodiscard]] char prettyRestriction() const;
    [[nodiscard]] bool exists() const;
    void satisfy();
    [[nodiscard]] bool pending() const;

private:
    int sum;
    int lightBulbs;
    int empties;
    int squares;
    bool enabled;
    bool satisfied;
};

}


#endif //LIGHT_UP_AGENT_RESTRICTION_H
