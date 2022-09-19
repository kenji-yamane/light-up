#include <iostream>

#include "modeling/Board.h"
#include "decision_making/ConstraintSatisfaction.h"

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
