#include "sdlwrap.h"
#include "GameState.h"
#include "EngineBase.h"
#include <SDL_timer.h>
#include <iostream>

int main(int, char* []) {
    EngineBase engine;
    engine.load_media();

    currentStateID() = GState::intro;
    currentState() = std::make_unique<StateIntro>(engine);

    StopWatch fpsCapper;
    while(currentStateID() != GState::exit) {
        fpsCapper.start();

        currentState()->handle_events();
        currentState()->handle_logic();

        change_state(engine);

        currentState()->handle_render(engine);

        if(fpsCapper.get_ticks() < minSpf) {
            SDL_Delay(minSpf - fpsCapper.get_ticks());
        }
    }
}
