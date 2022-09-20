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
    games.push_back(
        std::string("- - ? ? ? ? 1\n")+
        std::string("? ? ? ? ? ? 1\n")+
        std::string("? ? ? ? ? ? o\n")+
        std::string("? ? ? 0 ? ? o\n")+
        std::string("? ? ? ? ? ? o\n")+
        std::string("2 ? ? ? ? ? o\n")+
        std::string("- ? ? ? ? 1 -\n")
    );
    expectedSolutions.push_back(
        std::string("|-|-| | | |L|1|\n")+
        std::string("| | |L| | | |1|\n")+
        std::string("| | | | | | |L|\n")+
        std::string("| | | |0| | | |\n")+
        std::string("|L| | | | | | |\n")+
        std::string("|2|L| | | | | |\n")+
        std::string("|-| | | |L|1|-|\n")
    );

    games.push_back(
        std::string("? ? ? ? - ? o\n")+
        std::string("? ? ? 3 ? ? o\n")+
        std::string("0 ? ? ? ? ? o\n")+
        std::string("? 1 ? ? ? - o\n")+
        std::string("? ? ? ? ? ? 3\n")+
        std::string("? ? ? - ? ? o\n")+
        std::string("? ? 2 ? ? ? o\n")
    );
    expectedSolutions.push_back(
        std::string("| | | |L|-|L| |\n")+
        std::string("| |L| |3|L| | |\n")+
        std::string("|0| | |L| | | |\n")+
        std::string("| |1|L| | |-|L|\n")+
        std::string("| | | | | |L|3|\n")+
        std::string("|L| | |-| | |L|\n")+
        std::string("| |L|2|L| | | |\n")
    );

    games.push_back(
        std::string("0 ? - 0 ? ? 0\n")+
        std::string("? ? ? ? ? ? o\n")+
        std::string("? ? ? ? ? ? -\n")+
        std::string("0 ? ? ? ? ? 2\n")+
        std::string("- ? ? ? ? ? o\n")+
        std::string("? ? ? ? ? ? o\n")+
        std::string("1 ? ? 0 0 ? -\n")
    );
    expectedSolutions.push_back(
        std::string("|0| |-|0| | |0|\n")+
        std::string("| | | | |L| | |\n")+
        std::string("| | | |L| | |-|\n")+
        std::string("|0| | | | |L|2|\n")+
        std::string("|-| | | | | |L|\n")+
        std::string("| | |L| | | | |\n")+
        std::string("|1|L| |0|0| |-|\n")
    );

    for (int i = 0; i < (int)games.size(); i++) {
        if (not testCase(games[i], expectedSolutions[i])) {
            return -1;
        }
    }
    return 0;
}


