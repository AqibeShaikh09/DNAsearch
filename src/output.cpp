#include "output.h"
#include <iostream>

void output_results(const std::vector<size_t>& positions, const std::string& pattern) {
    if (positions.empty()) {
        std::cout << "Pattern \"" << pattern << "\" : NOT FOUND in genome\n";
        return;
    }
    std::cout << "Pattern \"" << pattern << "\" : "
              << positions.size() << " match(es) found\n";
    for (size_t i = 0; i < positions.size(); i++)
        std::cout << "  [" << i + 1 << "] byte offset: " << positions[i] << "\n";
}
