#include "input.h"
#include <iostream>

bool input_read_pattern(std::string& out) {
    return static_cast<bool>(std::getline(std::cin, out));
}
