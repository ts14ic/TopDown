#pragma once

#include <iosfwd>

namespace files {
    /**
     * Read whole file into a string
     * @param file_path The file location
     * @return File content
     * @throws runtime_error if failed to read the file
     */
    std::string read_file_to_string(const char *file_path);
}

