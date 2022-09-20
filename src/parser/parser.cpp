//
// Created by kenji on 19/09/22.
//

#include "parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

namespace parser {

modeling::Board fromFile(const std::string& filename) {
    std::ifstream in(filename);

    std::string fileContent((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return fromString(fileContent);
}

modeling::Board fromString(const std::string &board) {
    std::stringstream boardStream(board);

    std::string rowStr;
    std::vector<std::vector<char> > boardMatrix;
    while (std::getline(boardStream, rowStr)) {
        std::stringstream rowStream(rowStr);

        char c;
        std::vector<char> row;
        while (rowStream >> c) {
            row.push_back(c);
        }
        boardMatrix.push_back(row);
    }
    return parseBoard(boardMatrix);
}

modeling::Board parseBoard(const std::vector<std::vector<char> >& boardMatrix) {
    for (const auto &row : boardMatrix) {
        if (boardMatrix.size() != row.size()) {
            std::cerr << "board should be a square" << std::endl;
            exit(0);
        }
    }

    modeling::Board board((int)boardMatrix.size());
    for (int row = 0; row < (int)boardMatrix.size(); row++) {
        for (int column = 0; column < (int)boardMatrix[row].size(); column++) {
            if (boardMatrix[row][column] == '-') {
                board.addWall(row, column);
            } else if (std::isdigit(boardMatrix[row][column])) {
                board.addNumberedWall(row, column, boardMatrix[row][column] - '0');
            }
        }
    }
    return board;
}

}
