#include "game/GameImpl.h"
#include "sdl/SdlContextInjector.h"
#include "utils/sys/abort_handlers.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(int, char* []) {
    install_abort_handlers();
    GameImpl{
            WINDOW_WIDTH, WINDOW_HEIGHT,
            std::make_unique<SdlContextInjector>().get()
    }.run_loop();
}
