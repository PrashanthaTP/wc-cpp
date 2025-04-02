#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ccwc.hpp"

using std::cerr;
using std::cout;
using std::string;
using std::vector;

//
uint32_t getByteCount(const string& filePath) {
    std::ifstream file(filePath, std::ifstream::binary);
    if (file.is_open()) {
        file.seekg(0,file.end);
        uint32_t nBytes = file.tellg();
        return nBytes;
        
    } else {
        throw std::runtime_error("Error opening file: " + filePath + "\n");
    }
}
