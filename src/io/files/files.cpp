#include "files.h"
#include <fstream>
#include <sstream>

using namespace std::string_literals;

std::string files::read_file_to_string(const char* file_path) {
    std::ifstream file{file_path};
    if (!file) {
        throw std::runtime_error{"Failed to open file: "s + file_path};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
