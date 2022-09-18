#include <iostream>

#include "modeling/Variable.h"

int main() {
    modeling::Variable v;
    std::cout << "number of restrictions: " << v.restrictionsCount << std::endl;
    std::cout << "undefined: " << (v.value == modeling::Domain::UNDEFINED ? "yes" : "no") << std::endl;
    return 0;
}
