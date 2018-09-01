#include "abort_handlers.h"
#include "demangle_type_name.h"

#ifdef __GNUG__

#include <csignal>
#include <cstring>
#include <execinfo.h>
#include <iostream>

void print_stack_trace() {
    std::cerr << "Stack trace:" << std::endl;

    constexpr int max_frames = 10;
    void* frame_list[max_frames];
    int frame_count = backtrace(frame_list, max_frames);
    char** symbols = backtrace_symbols(frame_list, frame_count);

    for (int i = 0; i < frame_count; ++i) {
        char* symbol = symbols[i];

        char* name_start = nullptr;
        char* offset_start = nullptr;
        char* offset_end = nullptr;

        // find parentheses and +address offset surrounding the mangled name:
        // ./module(function+0x15c) [0x8048a6d]
        for (char* p = symbol; *p; ++p) {
            if (*p == '(') {
                name_start = p;
            } else if (*p == '+') {
                offset_start = p;
            } else if (*p == ')' && offset_start) {
                offset_end = p;
                break;
            }
        }

        if (name_start != nullptr && offset_start && offset_end && (name_start < offset_start)) {
            *name_start++ = '\0';
            *offset_start++ = '\0';
            *offset_end = '\0';


            std::string ret = utils::demangle_type_name(name_start);

            std::cerr << "\t" << symbol << ": " << ret.c_str() << " at " << offset_start << std::endl;
        } else {
            // couldn't parse the line? print the whole line.
            std::cerr << "\t" << symbol << std::endl;
        }
    }
}

void print_exception() {
    try {
        auto exception_ptr = std::current_exception();
        if (exception_ptr != nullptr) {
            std::rethrow_exception(exception_ptr);
        }
    } catch (const std::exception& ex) {
        std::cerr << "Uncaught exception: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception type." << std::endl;
    }
}

void print_signal(int signal) {
    std::cerr << strsignal(signal) << std::endl;
}

void sigsegv_handler(int sig) {
    print_signal(sig);
    print_stack_trace();
    exit(1);
}

void terminate_handler() {
    print_exception();
    print_stack_trace();
    abort();
}

#endif // __GNUG__

void install_abort_handlers() {
#ifdef __GNUG__
    std::signal(SIGSEGV, sigsegv_handler);
    std::set_terminate(terminate_handler);
#endif // __GNUG__
}