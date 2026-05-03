#include <iostream>
#include <cassert>
#include "../src/hash_cache.h"

void test_store_and_lookup() {
    HashCache cache(16);

    // Simulate caching search results for a gene pattern
    std::vector<size_t> positions = {102, 580, 4210};
    cache.store("ATGCGT", positions);

    const CacheEntry* r = cache.lookup("ATGCGT");
    assert(r != nullptr);
    assert(r->positions.size() == 3);
    assert(r->positions[1] == 580);
    std::cout << "  [PASS] cached nucleotide pattern retrieved correctly\n";

    const CacheEntry* miss = cache.lookup("TTTTTT");
    assert(miss == nullptr);
    std::cout << "  [PASS] uncached pattern returns nullptr\n";
}

int main() {
    std::cout << "=== Hash Cache Tests (DNA) ===\n";
    test_store_and_lookup();
    std::cout << "All Cache tests passed.\n";
    return 0;
}
