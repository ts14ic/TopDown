#include "files.h"
#include <fstream>
#include <sstream>

using namespace std::string_literals;

std::string files::read_file_to_string(cstring file_path) {
    std::ifstream file{file_path};
    if (file.fail()) {
        throw std::runtime_error{"Failed to open file: "s + file_path};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
