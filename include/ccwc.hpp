#pragma once

#include <string>
#include <cstdint>

uint32_t getByteCount(const std::string& filePath);
uint32_t getLineCount(const std::string& filePath);
uint32_t getWordCount(const std::string& filePath);
