#include "json.h"
#include <rapidjson/error/en.h>

using namespace std::string_literals;

RjDocument json::parse_json(const std::string& input) {
    RjDocument doc;
    doc.Parse(input.c_str(), input.length());
    if (doc.HasParseError()) {
        throw std::runtime_error{rapidjson::GetParseError_En(doc.GetParseError())};
    }
    return doc;
}

json::ParseException::ParseException(const std::string& message)
        : runtime_error(message) {}

using RjPointer = rapidjson::Pointer;

RjPointer get_pointer(const char* source) {
    RjPointer pointer{source};
    if (!pointer.IsValid()) {
        throw json::ParseException("Invalid pointer: "s + source);
    }
    return pointer;
}

const RjValue* json::detail::get_value(
        const RjValue& root,
        const char* source
) {
    auto pointer = get_pointer(source);
    auto value = pointer.Get(root);
    if (value == nullptr) {
        throw ParseException{"No value on path: "s + source};
    }
    return value;
}

RjObject json::get_object(const RjValue& root, const char* path) {
    return get_value<RjObject>(root, path);
}

RjArray json::get_array(const RjValue& root, const char* path) {
    return get_value<RjArray>(root, path);
}

const char* json::get_czstring(const RjValue& root, const char* source) {
    return get_value<const char*>(root, source);
}

int json::get_int(const RjValue& root, const char* source) {
    return get_value<int>(root, source);
}

unsigned json::get_uint(const RjValue& root, const char* source) {
    return get_value<unsigned>(root, source);
}
