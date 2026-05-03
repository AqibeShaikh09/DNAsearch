cmake_minimum_required(VERSION 3.15)
project(DNASearchSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    message(STATUS "Platform: Windows")
    add_compile_definitions(PLATFORM_WINDOWS)
else()
    message(STATUS "Platform: Unix/macOS")
    add_compile_definitions(PLATFORM_UNIX)
endif()

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -O2)
endif()

set(SOURCES
    src/main.cpp
    src/kmp.cpp
    src/bm.cpp
    src/mmap_reader.cpp
    src/suffix_array.cpp
    src/hash_cache.cpp
    src/input.cpp
    src/output.cpp
)

add_executable(dna_search ${SOURCES})

if(UNIX AND NOT APPLE)
    target_link_libraries(dna_search m)
endif()

set(TEST_SHARED_SOURCES
    src/kmp.cpp
    src/bm.cpp
    src/mmap_reader.cpp
    src/suffix_array.cpp
    src/hash_cache.cpp
    src/output.cpp
    src/input.cpp
)

add_executable(test_kmp          tests/test_kmp.cpp          ${TEST_SHARED_SOURCES})
add_executable(test_bm           tests/test_bm.cpp           ${TEST_SHARED_SOURCES})
add_executable(test_suffix_array tests/test_suffix_array.cpp ${TEST_SHARED_SOURCES})
add_executable(test_cache        tests/test_cache.cpp        ${TEST_SHARED_SOURCES})

enable_testing()
add_test(NAME KMP         COMMAND test_kmp)
add_test(NAME BoyerMoore  COMMAND test_bm)
add_test(NAME SuffixArray COMMAND test_suffix_array)
add_test(NAME Cache       COMMAND test_cache)
