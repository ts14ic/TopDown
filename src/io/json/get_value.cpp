#include "get_value.h"

json::JsonParseException::JsonParseException(const std::string& message)
        : runtime_error(message) {}

rapidjson::Pointer json::check_pointer(const char* pointer_path) {
    rapidjson::Pointer pointer{pointer_path};
    if (!pointer.IsValid()) {
        throw JsonParseException(std::string{"Invalid pointer: "} + pointer_path);
    }
    return pointer;
}

const rapidjson::Value*
json::check_value(const rapidjson::Value& root, const rapidjson::Pointer& pointer, const char* pointer_path) {
    auto value = pointer.Get(root);
    if (value == nullptr) {
        throw JsonParseException{std::string{"No value on path: "} + pointer_path};
    }
    return value;
}

rapidjson::Value::ConstObject json::get_object(const rapidjson::Value& root, const char* path) {
    return get_value<rapidjson::Value::ConstObject>(root, path);
}

const char* json::get_czstring(const rapidjson::Value& root, const char* path) {
    return get_value<const char*>(root, path);
}
