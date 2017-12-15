#include "engine/DefaultEngine.h"
#include "sdl/SdlContextInjector.h"

int main(int, char* []) {
    DefaultEngine{
            800, 600,
            std::make_unique<SdlContextInjector>().get()
    }.runLoop();
}
