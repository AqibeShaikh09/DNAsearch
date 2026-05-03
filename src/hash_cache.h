#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct CacheEntry {
    std::vector<size_t> positions;
};

// Simple cache wrapping unordered_map — O(1) average lookup
class HashCache {
public:
    explicit HashCache(size_t /*slots*/) {}   // slots kept for API compat

    // Returns nullptr if pattern not cached
    const CacheEntry* lookup(const std::string& pattern) const;

    // Store a result (no-op if already present)
    void store(const std::string& pattern, const std::vector<size_t>& positions);

private:
    std::unordered_map<std::string, CacheEntry> table_;
};
