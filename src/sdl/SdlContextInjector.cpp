//
// Created by ts14ic on 12/13/17.
//

#include "SdlContextInjector.h"
#include "SdlGraphicContext.h"
#include "SdlAudioContext.h"
#include "SdlInputContext.h"
#include "SdlResources.h"
#include "../engine/Engine.h"

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

void SdlContextInjector::inject(Engine& engine, int screenWidth, int screenHeight) {
    auto resources = createResources(screenWidth, screenHeight);
    auto graphic = createGraphicContext(resources->getWindow(), resources->getRenderer());

    engine.setResources(std::move(resources));
    engine.setGraphicContext(std::move(graphic));
    engine.setAudioContext(createAudioContext());
    engine.setInputContext(createInputContext());
}