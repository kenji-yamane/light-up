#include <iostream>

#include "parser/parser.h"
#include "decision_making/ConstraintSatisfaction.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "usage: provide the name of the file containing the game" << std::endl;
        std::cout << "./agent <name-of-the-file>" << std::endl;
        return 1;
    }
    modeling::Board board = parser::fromFile(std::string(argv[1]));

    decision_making::ConstraintSatisfaction agent(board);
    bool solvable = agent.solve();
    std::cout << "number of iterations: " << agent.nodesVisited << std::endl;
    if (not solvable) {
        std::cout << "no solution was found" << std::endl;
        return 0;
    }
    std::string solution = agent.solution.print();
    std::cout << solution;
    return 0;
}
