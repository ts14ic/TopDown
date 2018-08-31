#include "SdlContextInjector.h"
#include "SdlGraphicContext.h"
#include "SdlAudioContext.h"
#include "SdlInputContext.h"
#include "SdlResources.h"
#include "utils/random/Mt19937Random.h"

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

void SdlContextInjector::inject(Engine& engine, int screenWidth, int screenHeight) {
    auto resources = createResources(screenWidth, screenHeight);
    auto graphic = createGraphicContext(resources->getWindow(), resources->getRenderer());

    engine.setResources(std::move(resources));
    engine.setRandom(createRandom());
    engine.setGraphicContext(std::move(graphic));
    engine.setAudioContext(createAudioContext());
    engine.setInputContext(createInputContext());
}
