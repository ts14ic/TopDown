#pragma once

#include "GameState.h"
#include "game/Game.h"
#include <string>

class StateIntro : public GameState {
public:
    explicit StateIntro(Game& engine);

    void handle_window_event(const WindowEvent &event) override;

    void handle_mouse_event(const MouseEvent &event) override;

    void handle_key_event(const KeyboardEvent &event) override;

    void handle_logic() override;

    void handle_render(float predictionRatio) override;

private:
    Game& _engine;
    std::string _background_tex_id;
};

