//
// Created by ts14ic on 12/13/17.
//

#include "parseJson.h"
#include <rapidjson/error/en.h>

using namespace std::string_literals;

rapidjson::Document parseJson(const std::string& input) {
    rapidjson::Document doc;
    doc.Parse(input.c_str(), input.length());
    if(doc.HasParseError()) {
        throw std::runtime_error{rapidjson::GetParseError_En(doc.GetParseError())};
    }
    return doc;
}
