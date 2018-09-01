#pragma once

#include "utils/sys/demangle_type_name.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#undef RAPIDJSON_HAS_STDSTRING

#include <vector>

namespace json {
    const auto SOURCE_SELF = "";

    struct ParseException : public std::runtime_error {
        explicit ParseException(const std::string& message);
    };

    namespace detail {
        const rapidjson::Value* get_value(const rapidjson::Value& root, const char* source);

        template <class T>
        T get_value_casted(const rapidjson::Value& root, const char* source);
    }

    template <typename T>
    T get_value(const rapidjson::Value& root, const char* source = SOURCE_SELF);

    rapidjson::Value::ConstObject get_object(const rapidjson::Value& root, const char* path = SOURCE_SELF);

    const char* get_czstring(const rapidjson::Value& root, const char* path = SOURCE_SELF);

    template <typename T>
    std::vector<T> get_values(const rapidjson::Value& root, const char* source = SOURCE_SELF);
}

template <class T>
T json::detail::get_value_casted(const rapidjson::Value& root, const char* source) {
    auto value = get_value(root, source);

    // Despite the docs saying Is<> and Get<> work only on scalars,
    // this also works for ConstArray and ConstObject.
    if (!value->Is<T>()) {
        using namespace std::string_literals;
        throw ParseException{
                "Value on "s + source + " is not of type " + utils::demangle_type_name(typeid(T).name())
        };
    }
    return value->Get<T>();
}

template <typename T>
T json::get_value(const rapidjson::Value& root, const char* source) {
    return detail::get_value_casted<T>(root, source);
}

template <typename T>
std::vector<T> json::get_values(const rapidjson::Value& root, const char* source) {
    auto array = detail::get_value_casted<rapidjson::Value::ConstArray>(root, source);

    std::vector<T> vector;
    vector.reserve(array.Size());
    for (const auto& value : array) {
        vector.emplace_back(value.Get<T>());
    }
    return vector;
}
