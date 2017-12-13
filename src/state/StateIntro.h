//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../state/GameState.h"
#include "../assets/Texture.h"
#include <string>

class Engine;

class StateIntro : public GameState {
public:
    explicit StateIntro(Engine& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(Engine& engine) override;

private:
    std::string mBackgroundTexId;
};

