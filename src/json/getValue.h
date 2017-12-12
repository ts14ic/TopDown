//
// Created by ts14ic on 12/12/17.
//
#pragma once

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

class JsonParseException : public std::runtime_error {
public:
    explicit JsonParseException(const std::string& message)
            : runtime_error(message) {}
};

template <typename T>
bool checkValueType(const rapidjson::Value& value);

template <>
bool checkValueType<int>(const rapidjson::Value& value) {
    return value.IsInt();
}

template <>
bool checkValueType<unsigned>(const rapidjson::Value& value) {
    return value.IsUint();
}

template <>
bool checkValueType<const char*>(const rapidjson::Value& value) {
    return value.IsString();
}

template <>
bool checkValueType<rapidjson::Value::ConstObject>(const rapidjson::Value& value) {
    return value.IsObject();
}

template <>
bool checkValueType<rapidjson::Value::ConstArray>(const rapidjson::Value& value) {
    return value.IsArray();
}

template <typename T>
T getValue(const rapidjson::Value& root, const char* pointerPath) {
    rapidjson::Pointer pointer{pointerPath};
    if(!pointer.IsValid()) {
        throw JsonParseException{std::string{"Invalid pointer: "} + pointerPath};
    }
    auto value = pointer.Get(root);
    if(value == nullptr) {
        throw JsonParseException{std::string{"Failed to get missing "} + pointerPath};
    }

    if(!checkValueType<T>(*value)) {
        throw JsonParseException{std::string{"Value "} + pointerPath + " is not of type " + typeid(T).name()};
    }

    return value->Get<T>();
}

