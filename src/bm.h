#pragma once
#include "kmp.h"  

SearchResult bm_search(const char* text, size_t text_len, const std::string& pattern);
