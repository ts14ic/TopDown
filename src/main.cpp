#include "engine/DefaultEngine.h"
#include "sdl/SdlContextFactory.h"
#include "random/Mt19937Random.h"

int main(int, char* []) {
    // todo Use a factory to create assets and contexts
    DefaultEngine{
            std::make_unique<SdlContextFactory>(),
            std::make_unique<Mt19937Random>()
    }.runLoop();
}
