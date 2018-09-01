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
        const rapidjson::Value* get_value(
                const rapidjson::Value& root,
                const char* source
        );

        template <class T>
        T value_cast(const rapidjson::Value* value, const char* source) {
            // Despite the docs saying Is<> and Get<> work only on scalars,
            // this also works for ConstArray and ConstObject.
            if (!value->Is<T>()) {
                throw ParseException{
                        std::string{"Value on "} + source + " is not of type " +
                        utils::demangle_type_name(typeid(T).name())
                };
            }
            return value->Get<T>();
        }
    }

    template <typename T>
    T get_value(const rapidjson::Value& root, const char* source = SOURCE_SELF) {
        auto value = detail::get_value(root, source);
        return detail::value_cast<T>(value, source);
    }

    rapidjson::Value::ConstObject get_object(const rapidjson::Value& root, const char* path = SOURCE_SELF);

    const char* get_czstring(const rapidjson::Value& root, const char* path = SOURCE_SELF);

    template <typename T>
    std::vector<T> get_values(const rapidjson::Value& root, const char* source = SOURCE_SELF) {
        auto array_value = detail::get_value(root, source);
        auto array = detail::value_cast<rapidjson::Value::ConstArray>(array_value, source);

        std::vector<T> vector;
        vector.reserve(array.Size());
        for (const auto& value : array) {
            vector.emplace_back(value.Get<T>());
        }
        return vector;
    }
}