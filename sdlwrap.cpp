#include "sdlwrap.h"

int& screenWidth() {
    static int ret = 800;
    return ret;
}

int& screenHeight() {
    static int ret = 600;
    return ret;
}
