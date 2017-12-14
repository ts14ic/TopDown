#include "engine/DefaultEngine.h"
#include "sdl/SdlContextInjector.h"
#include "random/Mt19937Random.h"

int main(int, char* []) {
    DefaultEngine{
            800, 600,
            std::make_unique<SdlContextInjector>()
    }.runLoop();
}
