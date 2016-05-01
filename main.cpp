#include "sdlwrap.h"

int main(int, char*[]) {
    if(!init_sdl()) {
        return -1;
    }
    
    close_sdl();
}
