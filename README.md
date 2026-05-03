# DNA Sequence Search System

A fast, disk-based genomic search system using:
- **Suffix Array** — indexes the genome file for fast candidate lookup
- **KMP + Boyer-Moore** — confirms exact nucleotide pattern matches
- **Memory-mapped I/O** — accesses large genome files without loading into RAM
- **Hash Cache** — caches repeated pattern search results

## Build — Mac / Linux
```bash
mkdir build && cd build
cmake ..
make
```

## Build — Windows (MinGW)
```bat
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

## Run
```bash
# Interactive mode
./bin/dna_search ../data/sequences/sample.fasta

# Single query mode
./bin/dna_search ../data/sequences/sample.fasta "ATGCGT"
```

## Run Tests
```bash
cd build
ctest --output-on-failure
```

## Nucleotide Patterns to Try
| Pattern       | Meaning                        |
|---------------|--------------------------------|
| ATG           | Start codon (begin of a gene)  |
| TAA           | Stop codon                     |
| ATGCGTACG     | Custom gene fragment           |
| TACGATCG      | Embedded pattern in seq_001    |
| ACGT          | All four nucleotides           |

## File Structure
```
src/
  main.cpp              entry point
  kmp.cpp / .h          KMP (short patterns <= 16 chars)
  bm.cpp  / .h          Boyer-Moore (longer patterns)
  mmap_reader.cpp / .h  cross-platform memory-mapped file access
  suffix_array.cpp / .h suffix array index
  hash_cache.cpp / .h   unordered_map-based result cache
  input.cpp / .h        stdin reading
  output.cpp / .h       result formatting
tests/
  test_kmp.cpp          KMP tests with DNA sequences
  test_bm.cpp           Boyer-Moore tests with gene patterns
  test_suffix_array.cpp suffix array tests with codons
  test_cache.cpp        cache tests with nucleotide patterns
data/sequences/
  sample.fasta          3 sample DNA sequences in FASTA format
```
