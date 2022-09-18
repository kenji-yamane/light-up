//
// Created by kenji on 17/09/22.
//

#ifndef LIGHT_UP_AGENT_RESTRICTION_H
#define LIGHT_UP_AGENT_RESTRICTION_H

#include <utility>
#include <vector>

#include "modeling/Variable.h"

namespace modeling {

class Restriction {
public:
    Restriction(int sum);
    void addSquare(int line, int column);
    Domain interpret() const;

    std::vector<std::pair<int, int> > squares;

private:
    int sum;
};

}


#endif //LIGHT_UP_AGENT_RESTRICTION_H
