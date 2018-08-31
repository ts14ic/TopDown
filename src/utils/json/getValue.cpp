#include "getValue.h"

json::JsonParseException::JsonParseException(const std::string& message)
        : runtime_error(message) {}

rapidjson::Pointer json::checkPointer(const char* pointerPath) {
    rapidjson::Pointer pointer{pointerPath};
    if(!pointer.IsValid()) {
        throw JsonParseException(std::string{"Invalid pointer: "} + pointerPath);
    }
    return pointer;
}

const rapidjson::Value*
json::checkValue(const rapidjson::Value& root, const rapidjson::Pointer& pointer, const char* pointerPath) {
    auto value = pointer.Get(root);
    if(value == nullptr) {
        throw JsonParseException{std::string{"No value on path: "} + pointerPath};
    }
    return value;
}
