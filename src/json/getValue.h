//
// Created by ts14ic on 12/12/17.
//
#pragma once

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

template <typename T>
bool isValueOfType(const rapidjson::Value& value) {
    return value.Is<T>();
}

template <>
bool isValueOfType<rapidjson::Value::ConstObject>(const rapidjson::Value& value);

template <>
bool isValueOfType<rapidjson::Value::ConstArray>(const rapidjson::Value& value);

class JsonParseException : public std::runtime_error {
public:
    explicit JsonParseException(const std::string& message);
};

rapidjson::Pointer checkPointer(const char* pointerPath);

const rapidjson::Value*
checkValue(const rapidjson::Value& root, const rapidjson::Pointer& pointer, const char* pointerPath);

const char* demangleTypeName(const char* typeName);

template <class T>
T checkValueType(const rapidjson::Value* value, const char* pointerPath) {
    if(!isValueOfType<T>(*value)) {
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

