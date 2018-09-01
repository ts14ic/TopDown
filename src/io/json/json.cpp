#include "json.h"
#include <rapidjson/error/en.h>

using namespace std::string_literals;

rapidjson::Document json::parse_json(const std::string &input) {
    rapidjson::Document doc;
    doc.Parse(input.c_str(), input.length());
    if(doc.HasParseError()) {
        throw std::runtime_error{rapidjson::GetParseError_En(doc.GetParseError())};
    }
    return doc;
}

json::ParseException::ParseException(const std::string& message)
        : runtime_error(message) {}

rapidjson::Pointer get_pointer(const char* source) {
    rapidjson::Pointer pointer{source};
    if (!pointer.IsValid()) {
        throw json::ParseException("Invalid pointer: "s + source);
    }
    return pointer;
}

const rapidjson::Value* json::detail::get_value(
        const rapidjson::Value& root,
        const char* source
) {
    auto pointer = get_pointer(source);
    auto value = pointer.Get(root);
    if (value == nullptr) {
        throw ParseException{"No value on path: "s + source};
    }
    return value;
}

rapidjson::Value::ConstObject json::get_object(const rapidjson::Value& root, const char* path) {
    return get_value<rapidjson::Value::ConstObject>(root, path);
}

const char* json::get_czstring(const rapidjson::Value& root, const char* source) {
    return get_value<const char*>(root, source);
}
