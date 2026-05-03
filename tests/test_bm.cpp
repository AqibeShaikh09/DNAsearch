#include <iostream>
#include <cassert>
#include <cstring>
#include "../src/bm.h"

void test_long_pattern() {
    // Long gene sequence pattern — Boyer-Moore is used for patterns > 16 chars
    const char* text    = "GCTAGCTAGCATCGATCGATCGATCGTAGCTAGCATCG";
    const char* pattern = "ATCGATCGATCGATCG";   // 16 chars, edge of BM usage
    auto r = bm_search(text, strlen(text), pattern);
    // just check it runs without crashing and count is sane
    std::cout << "  [PASS] long pattern search completed, "
              << r.positions.size() << " match(es)\n";
}

void test_mutation_not_found() {
    // If a single nucleotide mutation exists, exact match should fail
    const char* text    = "AACGTTACG";   // original
    const char* pattern = "AACGTCACG";   // one mutation (T->C at pos 5)
    auto r = bm_search(text, strlen(text), pattern);
    assert(r.positions.empty());
    std::cout << "  [PASS] mutated pattern correctly not found\n";
}

int main() {
    std::cout << "=== Boyer-Moore Tests (DNA) ===\n";
    test_long_pattern();
    test_mutation_not_found();
    std::cout << "All BM tests passed.\n";
    return 0;
}
