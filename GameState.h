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

void change_state(EngineBase& engine);

class GameState {
public:
    virtual void handle_events() = 0;

    virtual void handle_logic()  = 0;

    virtual void handle_render(EngineBase& engine) = 0;

    virtual ~GameState() {}
};

class StateIntro : public GameState {
public:
    StateIntro(EngineBase& engine);

    virtual void handle_events();

    virtual void handle_logic();

    virtual void handle_render(EngineBase& engine);

private:
    Texture _background;
};

class StateMoon : public GameState {
public:
    StateMoon(EngineBase& engine);

    virtual void handle_events();

    virtual void handle_logic();

    virtual void handle_render(EngineBase& engine);

    void restrict_pos(Object&);

private:
    Texture _texBackground;
    int const _levelWidth = 800;
    int const _levelHeight = 600;

    Player _pl;
    StopWatch _mobSpawner;
};

#endif // GAMESTATE_H_INCLUDED
