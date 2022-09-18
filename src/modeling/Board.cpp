//
// Created by kenji on 17/09/22.
//

#include "Board.h"

#include <iostream>

namespace modeling {

Board::Board() : Board(7) {
}

Board::Board(int size) : size(size) {
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
    return true;
}

void Board::initializeBoard() {
    this->boardMatrix.clear();
    for (int i = 0; i < this->size; i++) {
        std::vector<Node> nodeRow;
        for (int j = 0; j < this->size; j++) {
            nodeRow.push_back(Node{
                Variable(),
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
                        this->boardMatrix[pos.first][pos.second].variable.value = Domain::EMPTY;
                    }
                    break;
                case Domain::LIGHT_BULB:
                    for (const auto &pos : n.restriction.squares) {
                        auto affected = this->lightUp(pos.first, pos.second);
                        if (affected.empty()) {
                            return;
                        }
                    }
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

std::set<std::pair<int, int> > Board::lightUp(int line, int column) {
    std::set<std::pair<int, int> > affectedVariables;
    if (not this->assertLightBulb(line, column)) {
        this->boardMatrix[line][column].variable.value = Domain::IMPOSSIBLE;
        return affectedVariables;
    }
    this->boardMatrix[line][column].variable.value = Domain::LIGHT_BULB;
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
            this->boardMatrix[currLine][currColumn].variable.value = Domain::EMPTY;
            affectedVariables.insert(std::pair<int, int>(line, column));
            currLine += conn.first;
            currColumn += conn.second;
        }
    }
    return affectedVariables;
}

void Board::printBoard() {
    if (not this->assertViability()) {
        std::cout << "there is not a solution to the given problem" << std::endl;
        return;
    }
    for (const auto &row : this->boardMatrix) {
        std::cout << "|";
        for (const auto &n : row) {
            std::cout << n.variable.prettyDomain() << "|";
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
