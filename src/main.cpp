#include "game/GameImpl.h"
#include "engine_std/Mt19937Random.h"
#include "engine_sdl/graphic/SdlGraphic.h"
#include "engine_sdl/input/SdlInput.h"
#include "engine_sdl/SdlEngine.h"
#include "engine_sdl/audio/SdlAudio.h"
#include "utils/sys/abort_handlers.h"

int main(int, char* []) {
    install_abort_handlers();

    auto game = GameImpl{
            std::make_unique<SdlEngine>()
    };
    game.run_loop();
}
