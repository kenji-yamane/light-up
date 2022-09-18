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
}

Board::~Board() {
    for (auto &row : this->boardMatrix) {
        for (auto v : row) {
            delete v;
        }
    }
    for (auto &row : this->restrictionsMatrix) {
        for (auto r : row) {
            delete r;
        }
    }
}

void Board::initializeBoard() {
    this->boardMatrix.clear();
    for (int i = 0; i < this->size; i++) {
        std::vector<Variable*> variables;
        for (int j = 0; j < this->size; j++) {
            variables.push_back(new Variable());
        }
        this->boardMatrix.push_back(variables);
    }

    this->restrictionsMatrix.clear();
    this->restrictionsMatrix = std::vector<std::vector<Restriction*> >(
        this->size, std::vector<Restriction*>(this->size, nullptr)
    );
}

void Board::printBoard() {
    if (not this->assertViability()) {
        std::cout << "there is not a solution to the given problem" << std::endl;
        return;
    }
    for (const auto &row : this->boardMatrix) {
        std::cout << "|";
        for (const auto &v : row) {
            std::cout << v->prettyDomain() << "|";
        }
        std::cout << std::endl;
    }
}

bool Board::assertViability() {
    for (const auto &row : this->boardMatrix) {
        for (const auto &v : row) {
            if (v->value == Domain::IMPOSSIBLE) {
                return false;
            }
        }
    }
    return true;
}

}
