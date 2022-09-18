//
// Created by kenji on 17/09/22.
//

#include "Variable.h"

namespace modeling {

Variable::Variable() {
    this->restrictionsCount = 0;
    this->value = Domain::UNDEFINED;
}

}
