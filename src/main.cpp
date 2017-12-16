#include "engine/DefaultEngine.h"
#include "engine/sdl/SdlContextInjector.h"
#include "utils/abortHandlers.h"

int main(int, char* []) {
    installAbortHandlers();
    DefaultEngine{
            800, 600,
            std::make_unique<SdlContextInjector>().get()
    }.runLoop();
}
