#pragma once

#include <utils/typedefs.h>
#include <string>

class DebugInfo {
public:
    DebugInfo();

    explicit DebugInfo(std::string name);

    cstring get_name() const;

private:
    std::string _name;
};