#include "SdlContextInjector.h"
#include "SdlGraphicContext.h"
#include "SdlAudioContext.h"
#include "SdlInputContext.h"
#include "SdlResources.h"
#include "random/Mt19937Random.h"

std::unique_ptr<SdlGraphicContext> createGraphicContext(SDL_Window* window, SDL_Renderer* renderer) {
    return std::make_unique<SdlGraphicContext>(window, renderer);
}

std::unique_ptr<SdlInputContext> createInputContext() {
    return std::make_unique<SdlInputContext>();
}

std::unique_ptr<SdlResources> createResources(int screenWidth, int screenHeight) {
    return std::make_unique<SdlResources>(screenWidth, screenHeight);
}

std::unique_ptr<SdlAudioContext> createAudioContext() {
    return std::make_unique<SdlAudioContext>();
}

std::unique_ptr<Mt19937Random> createRandom() {
    return std::make_unique<Mt19937Random>();
}

void SdlContextInjector::inject(Game& engine, int screenWidth, int screenHeight) {
    auto resources = createResources(screenWidth, screenHeight);
    auto graphic = createGraphicContext(resources->get_window(), resources->get_renderer());

    engine.set_resources(std::move(resources));
    engine.set_random(createRandom());
    engine.set_graphic_context(std::move(graphic));
    engine.set_audio_context(createAudioContext());
    engine.set_input_context(createInputContext());
}
