//
// Created by kenji on 17/09/22.
//

#include "Board.h"

#include <iostream>
#include <algorithm>

namespace modeling {

Board::Board() : Board(7) {
}

Board::Board(int size) : size(size), lights(0), walls(0) {
    this->initializeBoard();
    this->connections = std::vector<std::pair<int, int> >{
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };
}

void Board::addWall(int line, int column) {
    if (not this->isPosValid(line, column)) {
        std::cout << "invalid command, ignoring..." << std::endl;
        return;
    }

    this->walls++;
    this->boardMatrix[line][column].variable.value = Domain::EMPTY;
    this->boardMatrix[line][column].wall = true;
}

void Board::addNumberedWall(int line, int column, int num) {
    if (not this->isPosValid(line, column) || this->boardMatrix[line][column].wall || num < 0) {
        std::cout << "invalid command, ignoring..." << std::endl;
        return;
    }

    this->addWall(line, column);
    this->boardMatrix[line][column].restriction = Restriction(num);
    this->boardMatrix[line][column].restrict = true;
}

bool Board::assertLightBulb(int line, int column) {
    for (const auto &conn : this->connections) {
        int neighborLine = line + conn.first, neighborColumn = column + conn.second;
        if (not this->isPosValid(neighborLine, neighborColumn)) {
            continue;
        }
        if (not this->boardMatrix[neighborLine][neighborColumn].restrict) {
            continue;
        }
        if (not this->boardMatrix[neighborLine][neighborColumn].restriction.canAddLightBulbs()) {
            return false;
        }
    }
    for (const auto &conn : this->connections) {
        int currLine = line + conn.first, currColumn = column + conn.second;
        while (this->isPosValid(currLine, currColumn) && !this->boardMatrix[currLine][currColumn].wall) {
            if (not this->assertEmpty(currLine, currColumn)) {
                return false;
            }
            currLine += conn.first;
            currColumn += conn.second;
        }
    }
    return true;
}

bool Board::assertEmpty(int line, int column) {
    if (this->boardMatrix[line][column].variable.value == Domain::EMPTY) {
        return true;
    }
    if (this->boardMatrix[line][column].variable.value != Domain::UNDEFINED) {
        return false;
    }
    for (const auto &conn : this->connections) {
        int neighborLine = line + conn.first, neighborColumn = column + conn.second;
        if (not this->isPosValid(neighborLine, neighborColumn)) {
            continue;
        }
        if (not this->boardMatrix[neighborLine][neighborColumn].restrict) {
            continue;
        }
        if (not this->boardMatrix[neighborLine][neighborColumn].restriction.canAddEmpty()) {
            return false;
        }
    }
    return true;
}

void Board::initializeBoard() {
    this->boardMatrix.clear();
    for (int i = 0; i < this->size; i++) {
        std::vector<Node> nodeRow;
        for (int j = 0; j < this->size; j++) {
            nodeRow.push_back(Node{
                Variable(i, j),
                Restriction(0),
                false,
                false
            });
        }
        this->boardMatrix.push_back(nodeRow);
    }
}

void Board::interpretRestrictions() {
    for (int line = 0; line < (int)this->boardMatrix.size(); line++) {
        for (int column = 0; column < (int)this->boardMatrix[line].size(); column++) {
            if (not this->boardMatrix[line][column].restrict) {
                continue;
            }
            for (const auto &step: connections) {
                int neighborLine = line + step.first, neighborColumn = column + step.second;
                if (not this->isPosValid(neighborLine, neighborColumn)) {
                    continue;
                }
                if (this->boardMatrix[neighborLine][neighborColumn].variable.value == Domain::UNDEFINED) {
                    this->boardMatrix[line][column].restriction.addSquare(neighborLine, neighborColumn);
                }
            }
        }
    }

    for (auto &row : this->boardMatrix) {
        for (auto &n : row) {
            if (not n.restrict) {
                continue;
            }
            Domain interpretation = n.restriction.interpret();
            switch (interpretation) {
                case Domain::EMPTY:
                    for (const auto &pos : n.restriction.squares) {
                        auto affected = this->lightDown(pos.first, pos.second);
                        if (affected.empty()) {
                            return;
                        }
                    }
                    n.restrict = false;
                    break;
                case Domain::LIGHT_BULB:
                    for (const auto &pos : n.restriction.squares) {
                        auto affected = this->lightUp(pos.first, pos.second);
                        if (affected.empty()) {
                            return;
                        }
                    }
                    n.restrict = false;
                    break;
                case Domain::IMPOSSIBLE:
                    for (const auto &pos : n.restriction.squares) {
                        this->boardMatrix[pos.first][pos.second].variable.value = Domain::IMPOSSIBLE;
                    }
                    return;
                case Domain::UNDEFINED:
                    break;
            }
        }
    }
}

std::list<std::pair<int, int> > Board::degreeHeuristic() {
    for (const auto &row : this->boardMatrix) {
        for (const auto &n : row) {
            if (not n.restrict) {
                continue;
            }
            for (const auto &square : n.restriction.squares) {
                this->boardMatrix[square.first][square.second].variable.restrictionsCount++;
            }
        }
    }

    std::vector<Variable> undefinedVariables;
    for (const auto &row : this->boardMatrix) {
        for (const auto &n : row) {
            if (n.variable.value == Domain::UNDEFINED) {
                undefinedVariables.push_back(n.variable);
            }
        }
    }
    std::sort(undefinedVariables.begin(), undefinedVariables.end(), compareVariables);

    std::list<std::pair<int, int> > prioritized;
    for (const auto &v : undefinedVariables) {
        prioritized.emplace_back(v.line, v.column);
    }
    return prioritized;
}

bool Board::enlightened() const {
    return (this->lights + this->walls == this->size*this->size);
}

std::set<std::pair<int, int> > Board::lightUp(int line, int column) {
    std::set<std::pair<int, int> > affectedVariables;
    if (not this->assertLightBulb(line, column)) {
        this->boardMatrix[line][column].variable.value = Domain::IMPOSSIBLE;
        return affectedVariables;
    }
    this->boardMatrix[line][column].variable.value = Domain::LIGHT_BULB;
    this->lights++;
    affectedVariables.insert(std::pair<int, int>(line, column));
    for (const auto &conn : this->connections) {
        int currLine = line + conn.first, currColumn = column + conn.second;
        if (not this->isPosValid(currLine, currColumn)) {
            continue;
        }
        if (this->boardMatrix[currLine][currColumn].restrict) {
            this->boardMatrix[currLine][currColumn].restriction.addLightBulb();
        }
        while (this->isPosValid(currLine, currColumn) && !this->boardMatrix[currLine][currColumn].wall) {
            if (not this->boardMatrix[currLine][currColumn].enlightened) {
                this->boardMatrix[currLine][currColumn].enlightened = true;
                this->lights++;
            }
            auto affectedFromDown = this->lightDown(currLine, currColumn);
            for (const auto &v : affectedFromDown) {
                affectedVariables.insert(std::pair<int, int>(v.first, v.second));
            }
            currLine += conn.first;
            currColumn += conn.second;
        }
    }
    return affectedVariables;
}

std::set<std::pair<int, int> > Board::lightDown(int line, int column) {
    std::set<std::pair<int, int> > affectedVariables;
    if (not this->assertEmpty(line, column)) {
        this->boardMatrix[line][column].variable.value = Domain::IMPOSSIBLE;
        return affectedVariables;
    }
    if (this->boardMatrix[line][column].variable.value == Domain::EMPTY) {
        return affectedVariables;
    }
    this->boardMatrix[line][column].variable.value = Domain::EMPTY;
    affectedVariables.insert(std::pair<int, int>(line, column));
    for (const auto &conn : this->connections) {
        int neighborLine = line + conn.first, neighborColumn = column + conn.second;
        if (not this->isPosValid(neighborLine, neighborColumn)) {
            continue;
        }
        if (this->boardMatrix[neighborLine][neighborColumn].restrict) {
            this->boardMatrix[neighborLine][neighborColumn].restriction.addEmpty();
        }
    }
    return affectedVariables;
}

void Board::print() {
    for (const auto &row : this->boardMatrix) {
        std::cout << "|";
        for (const auto &n : row) {
            if (n.restrict) {
                std::cout << n.restriction.prettyRestriction() << "|";
            } else if (n.wall) {
                std::cout << "-" << "|";
            } else {
                std::cout << n.variable.prettyDomain() << "|";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::assertViability() {
    for (const auto &row : this->boardMatrix) {
        for (const auto &n : row) {
            if (n.variable.value == Domain::IMPOSSIBLE) {
                return false;
            }
        }
    }
    return true;
}

bool Board::isPosValid(int line, int column) const {
    if (line < 0 || line >= this->size) {
        return false;
    }
    if (column < 0 || column >= this->size) {
        return false;
    }
    return true;
}

}
