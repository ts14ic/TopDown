//
// Created by ts14ic on 12/13/17.
//

#include "demangle.h"

#ifdef __GNUG__

#include <cxxabi.h>
#include <memory>

#endif

std::string demangleTypeName(const char* typeName) {
#ifdef __GNUC__
    int status{};
    std::unique_ptr<char, decltype(&std::free)> res{
            __cxxabiv1::__cxa_demangle(typeName, nullptr, nullptr, &status),
            std::free
    };
    return (status == 0) ? res.get() : typeName;
#else
    return typeName;
#endif
}