#pragma once

#include <utils/sys/demangle_type_name.h>

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#undef RAPIDJSON_HAS_STDSTRING

#include <iosfwd>
#include <vector>

using RjDocument = rapidjson::Document;
using RjValue = rapidjson::Value;
using RjObject = rapidjson::Value::ConstObject;
using RjArray = rapidjson::Value::ConstArray;

namespace json {
    /**
     * Builds a Document out of string
     * @param input Input string in JSON format
     * @return Document
     * @throws runtime_error if input is malformed
     */
    RjDocument parse_json(const std::string& input);

    struct ParseException : public std::runtime_error {
        explicit ParseException(const std::string& message);
    };

    namespace detail {
        const RjValue* get_value(const RjValue& root, cstring source);

        template<class T>
        T get_value_casted(const RjValue& root, cstring source);
    }

    const auto SOURCE_SELF = "";

    template<typename T>
    T get_value(const RjValue& root, cstring source = SOURCE_SELF);

    RjObject get_object(const RjValue& root, cstring path = SOURCE_SELF);

    RjArray get_array(const RjValue& root, cstring path = SOURCE_SELF);

    cstring get_czstring(const RjValue& root, cstring source = SOURCE_SELF);

    int get_int(const RjValue& root, cstring source = SOURCE_SELF);

    unsigned get_uint(const RjValue& root, cstring source = SOURCE_SELF);

    template<typename T>
    std::vector<T> get_values(const RjValue& root, cstring source = SOURCE_SELF);
}

#include "json.tcc"
