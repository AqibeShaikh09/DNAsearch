#include "bm.h"
#include <array>

static constexpr int ALPHA = 256;

static std::array<int,ALPHA> build_bad_char(const std::string& pattern) {
    std::array<int,ALPHA> bc;
    bc.fill(-1);
    for (int i = 0; i < static_cast<int>(pattern.size()); i++)
        bc[static_cast<unsigned char>(pattern[i])] = i;
    return bc;
}

SearchResult bm_search(const char* text, size_t text_len, const std::string& pattern) {
    SearchResult result;
    int m = static_cast<int>(pattern.size());
    int n = static_cast<int>(text_len);
    if (m == 0 || n == 0 || m > n) return result;

    auto bc = build_bad_char(pattern);
    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) j--;
        if (j < 0) {
            result.positions.push_back(static_cast<size_t>(s));
            s += (s + m < n) ? m - bc[static_cast<unsigned char>(text[s + m])] : 1;
        } else {
            int shift = j - bc[static_cast<unsigned char>(text[s + j])];
            s += (shift > 1) ? shift : 1;
        }
    }
    return result;
}
