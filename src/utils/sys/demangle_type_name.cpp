#include "demangle_type_name.h"

#ifdef __GNUG__

#include <cxxabi.h>
#include <memory>

#endif // __GNUG__

std::string utils::demangle_type_name(const char *typeName) {
#ifdef __GNUG__
    int status{};
    std::unique_ptr<char, decltype(&std::free)> res{
            __cxxabiv1::__cxa_demangle(typeName, nullptr, nullptr, &status),
            std::free
    };
    return (status == 0) ? res.get() : typeName;
#else
    return typeName;
#endif // __GNUG__
}
