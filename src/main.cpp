#include "engine/DefaultEngine.h"
#include "engine/sdl/SdlContextInjector.h"
#include "utils/abortHandlers.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(int, char* []) {
    installAbortHandlers();
    DefaultEngine{
            WINDOW_WIDTH, WINDOW_HEIGHT,
            std::make_unique<SdlContextInjector>().get()
    }.runLoop();
}
