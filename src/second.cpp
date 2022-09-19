#include <iostream>

#include "modeling/Board.h"
#include "decision_making/ConstraintSatisfaction.h"

int main() {
    modeling::Board board(7);
    board.addWall(0, 4);
    board.addNumberedWall(1, 3, 3);
    board.addNumberedWall(2, 0, 0);
    board.addNumberedWall(3, 1, 1);
    board.addWall(3, 5);
    board.addNumberedWall(4, 6, 3);
    board.addWall(5, 3);
    board.addNumberedWall(6, 2, 2);

    decision_making::ConstraintSatisfaction agent(board);
    bool solvable = agent.solve();
    std::cout << "number of iterations: " << agent.nodesVisited << std::endl;
    if (not solvable) {
        std::cout << "no solution was found" << std::endl;
        return 0;
    }
    agent.solution.print();
    return 0;
}
