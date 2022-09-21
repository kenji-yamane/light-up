//
// Created by kenji on 17/09/22.
//

#include "Board.h"

#include <iostream>
#include <sstream>
#include <algorithm>

namespace modeling {

Board::Board() : Board(7) {
}

Board::Board(int size) : size(size), lights(0), walls(0), impossible(false) {
    this->initializeBoard();
    this->connections = std::vector<std::pair<int, int> >{
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };
}

void Board::initializeBoard() {
    this->variableMatrix = std::vector<std::vector<Variable> >(
        this->size,std::vector<Variable>(this->size, Variable())
    );
    this->restrictionMatrix = std::vector<std::vector<Restriction> >(
        this->size,std::vector<Restriction>(this->size, Restriction())
    );
}

std::vector<std::pair<int, int> > Board::getAllNodes() {
    std::vector<std::pair<int, int> > nodes;
    for (int line = 0; line < (int)this->restrictionMatrix.size(); line++) {
        for (int column = 0; column < (int)this->restrictionMatrix[line].size(); column++) {
            nodes.emplace_back(line, column);
        }
    }
    return nodes;
}

std::vector<std::pair<int, int> > Board::getUndefinedNeighbors(int line, int column) {
    return this->getNeighbors(line, column, std::set<Domain>{Domain::UNDEFINED});
}

std::vector<std::pair<int, int> > Board::getWallNeighbors(int line, int column) {
    return this->getNeighbors(line, column, std::set<Domain>{Domain::WALL});
}

std::vector<std::pair<int, int> > Board::getNeighbors(int line, int column, std::set<Domain> filter) {
    std::vector<std::pair<int, int> > neighbors;
    for (const auto &conn : this->connections) {
        int neighborLine = line + conn.first, neighborColumn = column + conn.second;
        if (not this->isPosValid(neighborLine, neighborColumn)) {
            continue;
        }
        if (filter.find(this->variableMatrix[neighborLine][neighborColumn].value) == filter.end()) {
            continue;
        }
        neighbors.emplace_back(neighborLine, neighborColumn);
    }
    return neighbors;
}

std::vector<std::pair<int, int> > Board::getVisibleNodes(int line, int column) {
    std::vector<std::pair<int, int> > visibility;
    for (const auto &conn : this->connections) {
        int currLine = line + conn.first, currColumn = column + conn.second;
        while (this->isPosValid(currLine, currColumn)) {
            if (this->variableMatrix[currLine][currColumn].value == Domain::WALL) {
                break;
            }
            visibility.emplace_back(currLine, currColumn);
            currLine += conn.first;
            currColumn += conn.second;
        }
    }
    return visibility;
}

void Board::addWall(int line, int column) {
    if (not this->isPosValid(line, column)) {
        std::cout << "invalid command, ignoring..." << std::endl;
        return;
    }

    this->walls++;
    this->variableMatrix[line][column].value = Domain::WALL;
}

void Board::addNumberedWall(int line, int column, int num) {
    if (not this->isPosValid(line, column) || this->variableMatrix[line][column].value == Domain::WALL || num < 0) {
        std::cout << "invalid command, ignoring..." << std::endl;
        return;
    }
    if (this->variableMatrix[line][column].value != Domain::UNDEFINED) {
        std::cout << "board is inconsistent, exiting..." << std::endl;
        exit(0);
    }

    this->addWall(line, column);
    this->restrictionMatrix[line][column] = Restriction(num);
    this->restrictionMatrix[line][column].addSquares((int)this->getUndefinedNeighbors(line, column).size());
}

void Board::interpretRestrictions() {
    for (const auto &node : this->getAllNodes()) {
        if (not restrictionMatrix[node.first][node.second].pending()) {
            continue;
        }
        Domain interpretation = restrictionMatrix[node.first][node.second].interpret();
        std::set<Domain> restrictionRange = std::set<Domain>{Domain::EMPTY, Domain::LIGHT_BULB, Domain::UNDEFINED};
        switch (interpretation) {
            case Domain::EMPTY:
                for (const auto &neighbor : this->getNeighbors(
                    node.first, node.second, restrictionRange)
                ) {
                    this->lightDown(neighbor.first, neighbor.second);
                }
                break;
            case Domain::LIGHT_BULB:
                for (const auto &neighbor : this->getNeighbors(
                    node.first, node.second, restrictionRange)
                ) {
                    this->lightUp(neighbor.first, neighbor.second);
                }
                break;
            case Domain::IMPOSSIBLE:
                this->giveUp(node.first, node.second);
                return;
            case Domain::UNDEFINED:
                for (const auto &undefined : this->getUndefinedNeighbors(node.first, node.second)) {
                    this->variableMatrix[undefined.first][undefined.second].restrictions++;
                }
            case Domain::WALL:
                break;
        }
    }
}

std::list<std::pair<int, int> > Board::getUndefinedVariables() {
    std::vector<std::pair<int, std::pair<int, int> > > undefinedVariables;
    for (const auto &node : this->getAllNodes()) {
        if (this->variableMatrix[node.first][node.second].value == Domain::UNDEFINED) {
            undefinedVariables.emplace_back(
                this->variableMatrix[node.first][node.second].restrictions,
                std::make_pair(node.first, node.second)
            );
        }
    }
    std::sort(undefinedVariables.begin(), undefinedVariables.end(), std::greater<>());

    std::list<std::pair<int, int> > prioritized;
    for (const auto &v : undefinedVariables) {
        prioritized.emplace_back(v.second.first, v.second.second);
    }
    return prioritized;
}

std::set<std::pair<int, int> > Board::lightUp(int line, int column) {
    std::set<std::pair<int, int> > affectedVariables;
    for (const auto &wall : this->getWallNeighbors(line, column)) {
        if (not this->restrictionMatrix[wall.first][wall.second].addLightBulb()) {
            this->giveUp(line, column);
            return affectedVariables;
        }
    }
    for (const auto &visibleNode : this->getVisibleNodes(line, column)) {
        if (not this->variableMatrix[visibleNode.first][visibleNode.second].enlightened) {
            this->variableMatrix[visibleNode.first][visibleNode.second].enlightened = true;
            this->lights++;
        }
        auto affectedFromDown = this->lightDown(visibleNode.first, visibleNode.second);
        for (const auto &v : affectedFromDown) {
            affectedVariables.insert(std::pair<int, int>(v.first, v.second));
        }
    }
    this->variableMatrix[line][column].value = Domain::LIGHT_BULB;
    affectedVariables.insert(std::pair<int, int>(line, column));
    this->lights++;
    return affectedVariables;
}

std::set<std::pair<int, int> > Board::lightDown(int line, int column) {
    std::set<std::pair<int, int> > affectedVariables;
    if (this->variableMatrix[line][column].value == Domain::EMPTY) {
        return affectedVariables;
    }
    if (this->variableMatrix[line][column].value != Domain::UNDEFINED) {
        this->giveUp(line, column);
        return affectedVariables;
    }
    for (const auto &wall : this->getWallNeighbors(line, column)) {
        if (not this->restrictionMatrix[wall.first][wall.second].addEmpty()) {
            this->giveUp(line, column);
            return affectedVariables;
        }
    }
    this->variableMatrix[line][column].value = Domain::EMPTY;
    affectedVariables.insert(std::pair<int, int>(line, column));
    return affectedVariables;
}

std::string Board::print() {
    std::stringstream out;
    for (int i = 0; i < (int)this->variableMatrix.size(); i++) {
        out << "|";
        for (int j = 0; j < (int)this->variableMatrix[i].size(); j++) {
            if (this->restrictionMatrix[i][j].exists()) {
                out << this->restrictionMatrix[i][j].prettyRestriction() << "|";
            } else {
                out << this->variableMatrix[i][j].prettyDomain() << "|";
            }
        }
        out << std::endl;
    }
    return out.str();
}

bool Board::enlightened() const {
    return (this->lights + this->walls == this->size*this->size);
}

bool Board::assertViability() const {
    return not impossible;
}

void Board::giveUp(int line, int column) {
    this->variableMatrix[line][column].value = Domain::IMPOSSIBLE;
    this->impossible = true;
}

bool Board::isPosValid(int line, int column) const {
    return ((line >= 0 && line < this->size) && (column >= 0 && column < this->size));
}

}
