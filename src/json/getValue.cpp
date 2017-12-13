//
// Created by ts14ic on 12/13/17.
//
#include "getValue.h"

#ifdef __GNUC__

#include <cxxabi.h>
#include <memory>

#endif

template <>
bool isValueOfType<int>(const rapidjson::Value& value) {
    return value.IsInt();
}

template <>
bool isValueOfType<unsigned>(const rapidjson::Value& value) {
    return value.IsUint();
}

template <>
bool isValueOfType<const char*>(const rapidjson::Value& value) {
    return value.IsString();
}

template <>
bool isValueOfType<rapidjson::Value::ConstObject>(const rapidjson::Value& value) {
    return value.IsObject();
}

template <>
bool isValueOfType<rapidjson::Value::ConstArray>(const rapidjson::Value& value) {
    return value.IsArray();
}

rapidjson::Pointer checkPointer(const char* pointerPath) {
    rapidjson::Pointer pointer{pointerPath};
    if(!pointer.IsValid()) {
        throw JsonParseException(std::string{"Invalid pointer: "} + pointerPath);
    }
    return pointer;
}

const rapidjson::Value*
checkValue(const rapidjson::Value& root, const rapidjson::Pointer& pointer, const char* pointerPath) {
    auto value = pointer.Get(root);
    if(value == nullptr) {
        throw JsonParseException{std::string{"No value on path: "} + pointerPath};
    }
    return value;
}

JsonParseException::JsonParseException(const std::string& message)
        : runtime_error(message) {}


const char* demangleTypeName(const char* typeName) {
#ifdef __GNUC__
    int status{};
    std::unique_ptr<char, void (*)(void*)> res{
            __cxxabiv1::__cxa_demangle(typeName, nullptr, nullptr, &status),
            std::free
    };
    return (status == 0) ? res.get() : typeName;
#else
    return type.name();
#endif
}