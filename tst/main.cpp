//
// Created by kenji on 20/09/22.
//

#include <iostream>

#include "parser/parser.h"
#include "decision_making/ConstraintSatisfaction.h"

bool testCase(const std::string& game, const std::string& expectedSolution) {
    modeling::Board board = parser::fromString(game);

    decision_making::ConstraintSatisfaction agent(board);
    bool solvable = agent.solve();
    if (not solvable) {
        return false;
    }
    return (agent.solution.print() == expectedSolution);
}

int main() {
    std::vector<std::string> games, expectedSolutions;
    games.push_back(std::string("- - o o o o 1\n")+
                    std::string("o o o o o o 1\n")+
                    std::string("o o o o o o o\n")+
                    std::string("o o o 0 o o o\n")+
                    std::string("o o o o o o o\n")+
                    std::string("2 o o o o o o\n")+
                    std::string("- o o o o 1 -\n"));
    expectedSolutions.push_back(std::string("|-|-| | | |L|1|\n")+
                                std::string("| | |L| | | |1|\n")+
                                std::string("| | | | | | |L|\n")+
                                std::string("| | | |0| | | |\n")+
                                std::string("|L| | | | | | |\n")+
                                std::string("|2|L| | | | | |\n")+
                                std::string("|-| | | |L|1|-|\n"));

    games.push_back(std::string("o o o o - o o\n")+
                    std::string("o o o 3 o o o\n")+
                    std::string("0 o o o o o o\n")+
                    std::string("o 1 o o o - o\n")+
                    std::string("o o o o o o 3\n")+
                    std::string("o o o - o o o\n")+
                    std::string("o o 2 o o o o\n"));
    expectedSolutions.push_back(std::string("| | | |L|-|L| |\n")+
                                std::string("| |L| |3|L| | |\n")+
                                std::string("|0| | |L| | | |\n")+
                                std::string("| |1|L| | |-|L|\n")+
                                std::string("| | | | | |L|3|\n")+
                                std::string("|L| | |-| | |L|\n")+
                                std::string("| |L|2|L| | | |\n"));

    games.push_back(std::string("0 o - 0 o o 0\n")+
                    std::string("o o o o o o o\n")+
                    std::string("o o o o o o -\n")+
                    std::string("0 o o o o o 2\n")+
                    std::string("- o o o o o o\n")+
                    std::string("o o o o o o o\n")+
                    std::string("1 o o 0 0 o -\n"));
    expectedSolutions.push_back(std::string("|0| |-|0| | |0|\n")+
                                std::string("| | | | |L| | |\n")+
                                std::string("| | | |L| | |-|\n")+
                                std::string("|0| | | | |L|2|\n")+
                                std::string("|-| | | | | |L|\n")+
                                std::string("| | |L| | | | |\n")+
                                std::string("|1|L| |0|0| |-|\n"));

    for (int i = 0; i < (int)games.size(); i++) {
        if (not testCase(games[i], expectedSolutions[i])) {
            return -1;
        }
    }
    return 0;
}


