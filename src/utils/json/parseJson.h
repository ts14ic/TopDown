#pragma once

#include <rapidjson/document.h>
#include <iosfwd>

namespace json {

    /**
     * Builds a Document out of string
     * @param input Input string in JSON format
     * @return Document
     * @throws runtime_error if input is malformed
     */
    rapidjson::Document parseJson(const std::string& input);
}