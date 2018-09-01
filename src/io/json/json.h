#pragma once

#include "utils/sys/demangle_type_name.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#undef RAPIDJSON_HAS_STDSTRING

#include <iosfwd>
#include <vector>

namespace json {

    /**
     * Builds a Document out of string
     * @param input Input string in JSON format
     * @return Document
     * @throws runtime_error if input is malformed
     */
    rapidjson::Document parse_json(const std::string& input);

    struct ParseException : public std::runtime_error {
        explicit ParseException(const std::string& message);
    };

    namespace detail {
        const rapidjson::Value* get_value(const rapidjson::Value& root, const char* source);

        template <class T>
        T get_value_casted(const rapidjson::Value& root, const char* source);
    }

    const auto SOURCE_SELF = "";

    template <typename T>
    T get_value(const rapidjson::Value& root, const char* source = SOURCE_SELF);

    rapidjson::Value::ConstObject get_object(const rapidjson::Value& root, const char* path = SOURCE_SELF);

    rapidjson::Value::ConstArray get_array(const rapidjson::Value& root, const char* path = SOURCE_SELF);

    const char* get_czstring(const rapidjson::Value& root, const char* source = SOURCE_SELF);

    int get_int(const rapidjson::Value& root, const char* source = SOURCE_SELF);

    unsigned get_uint(const rapidjson::Value& root, const char* source = SOURCE_SELF);

    template <typename T>
    std::vector<T> get_values(const rapidjson::Value& root, const char* source = SOURCE_SELF);
}

#include "json.tcc"
