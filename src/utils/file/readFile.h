#pragma once

#include <iosfwd>

namespace file {
    /**
     * Reads whole file into a tring
     * @param filePath The file location
     * @return File content
     * @throws runtime_error if failed to read the file
     */
    std::string readFile(const char* filePath);
}

