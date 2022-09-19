//
// Created by kenji on 17/09/22.
//

#ifndef LIGHT_UP_AGENT_BOARD_H
#define LIGHT_UP_AGENT_BOARD_H

#include <set>
#include <list>

#include "modeling/Restriction.h"
#include "modeling/Variable.h"

namespace modeling {

struct Node {
    Variable variable;
    Restriction restriction;
    bool wall{};
    bool restrict{};
};

class Board {
public:
    Board();
    explicit Board(int size);

    void addWall(int line, int column);
    void addNumberedWall(int line, int column, int num);
    void interpretRestrictions();
    std::list<std::pair<int, int> > degreeHeuristic();
    bool assertViability();
    bool assertLightBulb(int line, int column);
    std::set<std::pair<int, int> > lightUp(int line, int column);
    void print();

private:
    void initializeBoard();
    [[nodiscard]] bool isPosValid(int line, int column) const;

    int size;
    std::vector<std::vector<Node> > boardMatrix;
    std::vector<std::pair<int, int> > connections;
};

}

#endif //LIGHT_UP_AGENT_BOARD_H
