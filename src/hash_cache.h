#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct CacheEntry {
    std::vector<size_t> positions;
};

class HashCache {
public:
    explicit HashCache(size_t /*slots*/) {}   

    const CacheEntry* lookup(const std::string& pattern) const;

    void store(const std::string& pattern, const std::vector<size_t>& positions);

private:
    std::unordered_map<std::string, CacheEntry> table_;
};
