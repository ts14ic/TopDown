//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include <iosfwd>

/**
 * Reads whole file into a tring
 * @param filePath The file location
 * @return File content
 * @throws @code std::runtime_error if failed to read the file
 */
std::string readFile(const char* filePath);
