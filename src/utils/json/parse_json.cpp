#include "parse_json.h"
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
