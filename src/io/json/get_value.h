#pragma once

#include "utils/sys/demangle_type_name.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#undef RAPIDJSON_HAS_STDSTRING

#include <vector>

namespace json {
    struct JsonParseException : public std::runtime_error {
        explicit JsonParseException(const std::string& message);
    };

    rapidjson::Pointer check_pointer(const char* pointer_path);

    const rapidjson::Value*
    check_value(const rapidjson::Value& root, const rapidjson::Pointer& pointer, const char* pointer_path);

    /*
     * Despite the docs saying Is<> and Get<> work only on scalars,
     * this also works for ConstArray and ConstObject
     */
    template <class T>
    T check_value_type(const rapidjson::Value* value, const char* pointer_path) {
        if (!value->Is<T>()) {
            throw JsonParseException{
                    std::string{"Value on "} + pointer_path + " is not of type " +
                    utils::demangle_type_name(typeid(T).name())};
        }
        return value->Get<T>();
    }

    template <typename T>
    T get_value(const rapidjson::Value& root, const char* pointer_path) {
        auto pointer = check_pointer(pointer_path);
        auto value = check_value(root, pointer, pointer_path);
        return check_value_type<T>(value, pointer_path);
    }

    template <typename T>
    std::vector<T>
    get_values(const rapidjson::Value& root, const char* pointer_path) {
        auto pointer = check_pointer(pointer_path);
        auto array_value = check_value(root, pointer, pointer_path);
        auto array = check_value_type<rapidjson::Value::ConstArray>(array_value, pointer_path);

        std::vector<T> vector;
        vector.reserve(array.Size());
        for (const auto& value : array) {
            vector.emplace_back(value.Get<T>());
        }
        return vector;
    }
}