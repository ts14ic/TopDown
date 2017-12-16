//
// Created by ts14ic on 12/16/17.
//

#include "abortHandlers.h"

#ifdef __GNUG__

#include <csignal>
#include <cstring>
#include "demangleTypeName.h"
#include <execinfo.h>
#include <iostream>

void printStackTrace() {
    std::cerr << "Stack trace:" << std::endl;

    int maxFrames = 10;
    void* framesList[maxFrames];
    int framesCount = backtrace(framesList, maxFrames);
    char** symbolsList = backtrace_symbols(framesList, framesCount);

    for(int i = 0; i < framesCount; ++i) {
        char* symbol = symbolsList[i];

        char* nameStart = nullptr;
        char* offsetStart = nullptr;
        char* offsetEnd = nullptr;

        // find parentheses and +address offset surrounding the mangled name:
        // ./module(function+0x15c) [0x8048a6d]
        for(char* p = symbol; *p; ++p) {
            if(*p == '(') {
                nameStart = p;
            } else if(*p == '+') {
                offsetStart = p;
            } else if(*p == ')' && offsetStart) {
                offsetEnd = p;
                break;
            }
        }

        if(nameStart && offsetStart && offsetEnd && (nameStart < offsetStart)) {
            *nameStart++ = '\0';
            *offsetStart++ = '\0';
            *offsetEnd = '\0';


            std::string ret = utils::demangleTypeName(nameStart);

            std::cerr << "\t" << symbol << ": " << ret.c_str() << " at " << offsetStart << std::endl;
        } else {
            // couldn't parse the line? print the whole line.
            std::cerr << "\t" << symbol << std::endl;
        }
    }
}

void printException() {
    try {
        auto exceptionPtr = std::current_exception();
        if(exceptionPtr) {
            std::rethrow_exception(exceptionPtr);
        }
    } catch(const std::exception& ex) {
        std::cerr << "Uncaught exception: " << ex.what() << std::endl;
    } catch(...) {
        std::cerr << "Unknown exception type." << std::endl;
    }
}

void printSignal(int signal) {
    std::cerr << strsignal(signal) << std::endl;
}

void signalHandler(int sig) {
    printSignal(sig);
    printStackTrace();
    exit(1);
}

void terminateHandler() {
    printException();
    printStackTrace();
    abort();
}

#endif // __GNUG__

void installAbortHandlers() {
#ifdef __GNUG__
    std::signal(SIGSEGV, signalHandler);
    std::set_terminate(terminateHandler);
#endif // __GNUG__
}