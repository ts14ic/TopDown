#pragma once

#include "Texture.h"
#include "GameObject.h"
#include <memory>

/* forward declarations begin */
union SDL_Event;

class GameState;

class Engine;

/* forward declarations end */

SDL_Event& gameEvent();

class GameState {
public:
    virtual void handle_events(Engine& engine) = 0;

    virtual void handle_logic(Engine& engine)  = 0;

    virtual void handle_render(RenderBase& engine) = 0;

    virtual ~GameState() = default;
};

class StateIntro : public GameState {
public:
    explicit StateIntro(RenderBase& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(RenderBase& engine) override;

private:
    Texture _background;
};

class StateMoon : public GameState {
public:
    explicit StateMoon(RenderBase& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(RenderBase& engine) override;

    void restrict_pos(Object&);

private:
    Texture _texBackground;
    int const _levelWidth = 800;
    int const _levelHeight = 600;

    Player _pl;
    StopWatch _mobSpawner;
};
