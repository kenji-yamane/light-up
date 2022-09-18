#include <iostream>

#include "modeling/Board.h"

int main() {
    modeling::Board board(7);
    board.addWall(0, 0);
    board.addWall(0, 1);
    board.addNumberedWall(0, 6, 1);
    board.addNumberedWall(1, 6, 1);
    board.addNumberedWall(3, 3, 0);
    board.addNumberedWall(5, 0, 2);
    board.addWall(6, 0);
    board.addNumberedWall(6, 5, 1);
    board.addWall(6, 6);
    board.interpretRestrictions();
    if (not board.assertViability()) {
        std::cout << "a solution does not exist" << std::endl;
        return 0;
    }
    std::cout << board.assertLightBulb(1, 5) << std::endl;
    board.printBoard();
    return 0;
}
