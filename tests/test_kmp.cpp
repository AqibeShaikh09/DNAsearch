#include <iostream>
#include <cassert>
#include <cstring>
#include "../src/kmp.h"

void test_basic_match() {
    // Simple sequence with one unambiguous match
    const char* text    = "AAAACGTAAAAA";
    const char* pattern = "ACGT";
    auto r = kmp_search(text, strlen(text), pattern);
    assert(r.positions.size() == 1);
    assert(r.positions[0] == 3);
    std::cout << "  [PASS] nucleotide pattern found at offset " << r.positions[0] << "\n";
}

void test_no_match() {
    const char* text = "AAAACCCCGGGGTTTT";
    auto r = kmp_search(text, strlen(text), "ACGT");
    assert(r.positions.empty());
    std::cout << "  [PASS] absent pattern returns empty\n";
}

void test_multiple_matches() {
    // ATG is the start codon — appears 3 times here
    const char* text    = "ATGCGATGAAATGCCC";
    auto r = kmp_search(text, strlen(text), "ATG");
    assert(r.positions.size() == 3);
    std::cout << "  [PASS] start codon ATG found " << r.positions.size() << " times\n";
}

int main() {
    std::cout << "=== KMP Tests (DNA) ===\n";
    test_basic_match();
    test_no_match();
    test_multiple_matches();
    std::cout << "All KMP tests passed.\n";
    return 0;
}
