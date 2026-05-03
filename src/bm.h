#pragma once
#include "kmp.h"  // reuse SearchResult

SearchResult bm_search(const char* text, size_t text_len, const std::string& pattern);
