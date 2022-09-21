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
    IMPOSSIBLE,
    WALL
};

class Variable {
public:
    Variable();

    void lightUp();
    [[nodiscard]] bool lit() const;

    void addRestriction();
    [[nodiscard]] int countRestrictions() const;

    [[nodiscard]] char prettyDomain() const;

    Domain value;

private:
    static std::map<Domain, char> domainToAscii;

    int restrictions;
    bool light;
};

}


#endif //LIGHT_UP_AGENT_VARIABLE_H
