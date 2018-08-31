#include "game/GameImpl.h"
#include "random/Mt19937Random.h"
#include "sdl/SdlGraphicContext.h"
#include "sdl/SdlInputContext.h"
#include "sdl/SdlEngine.h"
#include "sdl/SdlAudioContext.h"
#include "utils/sys/abort_handlers.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(int, char* []) {
    install_abort_handlers();

    auto resources = std::make_unique<SdlEngine>(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto graphic_context = std::make_unique<SdlGraphicContext>(resources->get_window(), resources->get_renderer());

    GameImpl{
            std::move(resources),
            std::make_unique<Mt19937Random>(),
            std::move(graphic_context),
            std::make_unique<SdlAudioContext>(),
            std::make_unique<SdlInputContext>()
    }.run_loop();
}
