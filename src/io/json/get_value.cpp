#include "get_value.h"

json::JsonParseException::JsonParseException(const std::string& message)
        : runtime_error(message) {}

rapidjson::Pointer json::detail::get_pointer(const char* source) {
    rapidjson::Pointer pointer{source};
    if (!pointer.IsValid()) {
        throw JsonParseException(std::string{"Invalid pointer: "} + source);
    }
    return pointer;
}

const rapidjson::Value* json::detail::get_value(
        const rapidjson::Value& root,
        const rapidjson::Pointer& pointer,
        const char* source
) {
    auto value = pointer.Get(root);
    if (value == nullptr) {
        throw JsonParseException{std::string{"No value on path: "} + source};
    }
    return value;
}

rapidjson::Value::ConstObject json::get_object(const rapidjson::Value& root, const char* path) {
    return get_value<rapidjson::Value::ConstObject>(root, path);
}

const char* json::get_czstring(const rapidjson::Value& root, const char* path) {
    return get_value<const char*>(root, path);
}
