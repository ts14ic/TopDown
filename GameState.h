#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "Texture.h"
#include <memory>

/* forward declarations begin */
union SDL_Event;
class GameState;
/* forward declarations end */

SDL_Event& gameEvent();

std::unique_ptr<GameState>& currentState();

enum class GState {
    null,
    intro,
    moon,
    score,
    exit
};

GState& currentStateID();
GState& nextStateID();

void prepare_state(GState stateID);
void change_state();

class GameState {
public:
    virtual void handle_events() = 0;
    virtual void handle_logic()  = 0;
    virtual void handle_render() = 0;
    virtual ~GameState() {}
};

#endif // GAMESTATE_H_INCLUDED
