#pragma once
#include <cstddef>
#include <string>

struct MmapHandle {
    const char* data = nullptr;
    size_t      size = 0;
    void*      _impl = nullptr;
};

// Open a file and memory-map it. Returns nullptr on failure.
MmapHandle* mmap_open(const std::string& filepath);

// Unmap and close. Always call when done.
void mmap_close(MmapHandle* handle);
