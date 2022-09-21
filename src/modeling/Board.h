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

class Board {
public:
    Board();
    explicit Board(int size);

    std::vector<std::pair<int, int> > getAllNodes();
    std::vector<std::pair<int, int> > getUndefinedNeighbors(int line, int column);
    std::vector<std::pair<int, int> > getWallNeighbors(int line, int column);
    std::vector<std::pair<int, int> > getNeighbors(int line, int column, std::set<Domain> filter);
    std::vector<std::pair<int, int> > getVisibleNodes(int line, int column);

    void addWall(int line, int column);
    void addNumberedWall(int line, int column, int num);
    void interpretRestrictions();
    std::list<std::pair<int, int> > getUndefinedVariables();
    bool assertViability();
    [[nodiscard]] bool enlightened() const;
    std::set<std::pair<int, int> > lightUp(int line, int column);
    std::set<std::pair<int, int> > lightDown(int line, int column);
    std::string print();

private:
    void initializeBoard();
    [[nodiscard]] bool isPosValid(int line, int column) const;

    int size;
    int lights;
    int walls;
    std::vector<std::vector<Variable> > variableMatrix;
    std::vector<std::vector<Restriction> > restrictionMatrix;
    std::vector<std::pair<int, int> > connections;
};

}

#endif //LIGHT_UP_AGENT_BOARD_H
