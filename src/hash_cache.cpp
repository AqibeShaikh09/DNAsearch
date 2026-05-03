#include "hash_cache.h"

const CacheEntry* HashCache::lookup(const std::string& pattern) const {
    auto it = table_.find(pattern);
    if (it == table_.end()) return nullptr;
    return &it->second;
}

void HashCache::store(const std::string& pattern, const std::vector<size_t>& positions) {
    if (table_.count(pattern)) return;   // already cached
    table_[pattern] = CacheEntry{positions};
}
