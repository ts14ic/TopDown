#include "demangle_type_name.h"

#ifdef __GNUG__

#include <cxxabi.h>
#include <memory>

#endif // __GNUG__

std::string utils::demangle_type_name(const char* type_name) {
#ifdef __GNUG__
    int status{};
    std::unique_ptr<char, decltype(&std::free)> res{
            __cxxabiv1::__cxa_demangle(type_name, nullptr, nullptr, &status),
            std::free
    };
    return (status == 0) ? res.get() : type_name;
#else
    return type_name;
#endif // __GNUG__
}
