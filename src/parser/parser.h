//
// Created by kenji on 19/09/22.
//

#ifndef LIGHT_UP_AGENT_PARSER_H
#define LIGHT_UP_AGENT_PARSER_H

#endif //LIGHT_UP_AGENT_PARSER_H

#include <vector>

#include "modeling/Board.h"

namespace parser {

modeling::Board fromFile(const std::string& filename);

modeling::Board fromString(const std::string &board);

modeling::Board parseBoard(const std::vector<std::vector<char> >& boardStr);

}
