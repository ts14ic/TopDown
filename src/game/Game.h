#pragma once

#include "engine/input/InputContext.h"
#include "engine/graphic/GraphicContext.h"
#include "engine/audio/AudioContext.h"
#include "engine/Resources.h"
#include "engine/random/Random.h"
#include "engine/clock/Clock.h"
#include "StateId.h"
#include <memory>

class Game {
public:
    virtual ~Game();

    virtual void run_loop() = 0;

    virtual void request_state_change(StateId stateId) = 0;

    virtual GraphicContext& get_graphic_context() = 0;

    virtual AudioContext& get_audio_context() = 0;

    virtual Resources& get_resources() = 0;

    virtual Random& get_random() = 0;

    virtual const Clock& get_clock() = 0;

    virtual void set_input_context(std::unique_ptr<InputContext> inputContext) = 0;

    virtual void set_graphic_context(std::unique_ptr<GraphicContext> graphicContext) = 0;

    virtual void set_audio_context(std::unique_ptr<AudioContext> audioContext) = 0;

    virtual void set_resources(std::unique_ptr<Resources> resources) = 0;

    virtual void set_random(std::unique_ptr<Random> random) = 0;
};
