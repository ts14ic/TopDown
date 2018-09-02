#pragma once

#include "StateId.h"
#include <engine/Engine.h>
#include <memory>

class Game {
public:
    virtual ~Game();

    virtual void run_loop() = 0;

    virtual void request_state_change(StateId stateId) = 0;

    virtual Engine& get_engine() = 0;
};
