#include "DebugInfo.h"

DebugInfo::DebugInfo() = default;

DebugInfo::DebugInfo(std::string name) :
        _name{std::move(name)} {
}

cstring DebugInfo::get_name() const {
    return _name.c_str();
}
