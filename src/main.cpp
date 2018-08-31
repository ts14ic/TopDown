#include "engine/DefaultEngine.h"
#include "engine/sdl/SdlContextInjector.h"
#include "utils/abort_handlers.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(int, char* []) {
    install_abort_handlers();
    DefaultEngine{
            WINDOW_WIDTH, WINDOW_HEIGHT,
            std::make_unique<SdlContextInjector>().get()
    }.run_loop();
}
