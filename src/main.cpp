#include <iostream>
#include <string>
#include <cstdlib>

#include "input.h"
#include "output.h"
#include "mmap_reader.h"
#include "suffix_array.h"
#include "hash_cache.h"
#include "kmp.h"
#include "bm.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <fasta_file> [pattern]\n";
        std::cerr << "  fasta_file : path to the large DNA sequence file (.fasta)\n";
        std::cerr << "  pattern    : (optional) nucleotide pattern to search for\n";
        return EXIT_FAILURE;
    }

    std::string filepath = argv[1];

    MmapHandle* handle = mmap_open(filepath);
    if (!handle) {
        std::cerr << "Error: could not open '" << filepath << "'\n";
        return EXIT_FAILURE;
    }

    std::cout << "=== DNA Sequence Search System ===\n";
    std::cout << "File  : " << filepath << "\n";
    std::cout << "Size  : " << handle->size << " bytes\n";

    std::cout << "\nBuilding suffix array index...\n";
    SuffixArray* sa = sa_build(handle->data, handle->size);
    if (!sa) {
        std::cerr << "Error: failed to build suffix array\n";
        mmap_close(handle);
        return EXIT_FAILURE;
    }
    std::cout << "Index built. " << sa->length << " suffixes indexed.\n";

    HashCache cache(128);

    auto do_search = [&](const std::string& pattern) {
        for (char c : pattern) {
            char u = toupper(c);
            if (u != 'A' && u != 'C' && u != 'G' && u != 'T') {
                std::cout << "Warning: '" << c
                          << "' is not a valid nucleotide (A/C/G/T). Searching anyway.\n";
                break;
            }
        }

        const CacheEntry* cached = cache.lookup(pattern);
        if (cached) {
            std::cout << "[cache hit]\n";
            output_results(cached->positions, pattern);
            return;
        }

        std::vector<size_t> candidates = sa_search(sa, pattern);

        SearchResult result;
        if (pattern.size() <= 16)
            result = kmp_search(handle->data, handle->size, pattern);
        else
            result = bm_search(handle->data, handle->size, pattern);

        cache.store(pattern, result.positions);
        output_results(result.positions, pattern);
    };

    if (argc >= 3) {
        do_search(argv[2]);
    } else {
        std::cout << "\nEnter nucleotide pattern to search (e.g. ACGT), or 'quit' to exit:\n";
        std::string pattern;
        while (true) {
            std::cout << "> ";
            if (!input_read_pattern(pattern)) break;
            if (pattern == "quit") break;
            if (pattern.empty()) continue;
            do_search(pattern);
        }
    }

    sa_free(sa);
    mmap_close(handle);
    std::cout << "Bye.\n";
    return EXIT_SUCCESS;
}
