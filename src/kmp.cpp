#include "kmp.h"
#include <vector>

static std::vector<int> build_lps(const std::string& pattern) {
    int m = static_cast<int>(pattern.size());
    std::vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0) len = lps[len - 1];
            else          lps[i++] = 0;
        }
    }
    return lps;
}

SearchResult kmp_search(const char* text, size_t text_len, const std::string& pattern) {
    SearchResult result;
    int m = static_cast<int>(pattern.size());
    int n = static_cast<int>(text_len);
    if (m == 0 || n == 0 || m > n) return result;

    auto lps = build_lps(pattern);
    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) { i++; j++; }
        if (j == m) {
            result.positions.push_back(static_cast<size_t>(i - j));
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else        i++;
        }
    }
    return result;
}
