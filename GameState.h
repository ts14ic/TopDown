#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "Texture.h"
#include "GameObject.h"
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

class StateIntro : public GameState {
public:
    StateIntro();
    
    virtual void handle_events();
    virtual void handle_logic();
    virtual void handle_render();
private:
    Texture _background;
};

class StateMoon : public GameState {
public:
    StateMoon();

    virtual void handle_events();
    virtual void handle_logic();
    virtual void handle_render();
private:
    Texture _texBackground;
    int const _levelWidth  = 800;
    int const _levelHeight = 600;
    
    Player _pl;
};

#endif // GAMESTATE_H_INCLUDED
