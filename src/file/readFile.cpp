//
// Created by ts14ic on 12/13/17.
//

#include "readFile.h"
#include <fstream>
#include <sstream>

using namespace std::string_literals;

std::string readFile(const char* filePath) {
    std::ifstream file{filePath};
    if(!file) {
        throw std::runtime_error{"Failed to open file: "s + filePath};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
