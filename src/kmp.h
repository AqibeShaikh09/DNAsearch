#pragma once
#include <vector>
#include <string>

struct SearchResult {
    std::vector<size_t> positions;
};

SearchResult kmp_search(const char* text, size_t text_len, const std::string& pattern);
