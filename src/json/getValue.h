//
// Created by ts14ic on 12/12/17.
//
#pragma once

#include "../utils/demangle.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#undef RAPIDJSON_HAS_STDSTRING

#include <vector>

struct JsonParseException : public std::runtime_error {
    explicit JsonParseException(const std::string& message);
};

rapidjson::Pointer checkPointer(const char* pointerPath);

const rapidjson::Value*
checkValue(const rapidjson::Value& root, const rapidjson::Pointer& pointer, const char* pointerPath);

/*
 * Despite the docs saying Is<> and Get<> work only on scalars,
 * this also works for ConstArray and ConstObject
 */
template <class T>
T checkValueType(const rapidjson::Value* value, const char* pointerPath) {
    if(!value->Is<T>()) {
        throw JsonParseException{
                std::string{"Value on "} + pointerPath + " is not of type " + demangleTypeName(typeid(T).name())};
    }
    return value->Get<T>();
}

template <typename T>
T getValue(const rapidjson::Value& root, const char* pointerPath) {
    auto pointer = checkPointer(pointerPath);
    auto value = checkValue(root, pointer, pointerPath);
    return checkValueType<T>(value, pointerPath);
}

template <typename T>
std::vector<T>
getValues(const rapidjson::Value& root, const char* pointerPath) {
    auto pointer = checkPointer(pointerPath);
    auto arrayValue = checkValue(root, pointer, pointerPath);
    auto array = checkValueType<rapidjson::Value::ConstArray>(arrayValue, pointerPath);

    std::vector<T> vector;
    vector.reserve(array.Size());
    for(const auto& value : array) {
        vector.emplace_back(value.Get<T>());
    }
    return vector;
}
