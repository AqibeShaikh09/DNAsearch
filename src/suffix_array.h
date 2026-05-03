#pragma once
#include <vector>
#include <string>
#include <cstddef>

struct SuffixArray {
    std::vector<size_t> array;   // array[i] = start offset of i-th sorted suffix
    const char*         text;
    size_t              length;
};

// Build suffix array from a buffer. O(n log n).
SuffixArray* sa_build(const char* text, size_t length);

// Binary search for pattern. Returns matching byte offsets.
std::vector<size_t> sa_search(const SuffixArray* sa, const std::string& pattern);

// Free the suffix array (does NOT free original text).
void sa_free(SuffixArray* sa);
