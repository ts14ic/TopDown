//
// Created by ts14ic on 12/13/17.
//

#include "DefaultEngine.h"
#include "../file/readFile.h"
#include "../json/getValue.h"
#include "../json/parseJson.h"

void DefaultEngine::loadResources() {
    auto doc = parseJson(readFile("data/common_media.json"));

    auto texturesMap = getValue<rapidjson::Value::ConstObject>(doc, "/textures");
    for(const auto& entry : texturesMap) {
        mResources->loadTexture(getValue<const char*>(entry.name, ""), getValue<const char*>(entry.value, ""));
    }

    auto soundsMap = getValue<rapidjson::Value::ConstObject>(doc, "/sounds");
    for(const auto& entry : soundsMap) {
        mResources->loadSound(getValue<const char*>(entry.name, ""), getValue<const char*>(entry.value, ""));
    }

    auto musicMap = getValue<rapidjson::Value::ConstObject>(doc, "/music");
    for(const auto& entry : musicMap) {
        mResources->loadMusic(getValue<const char*>(entry.name, ""), getValue<const char*>(entry.value, ""));
    }
}

AudioContext& DefaultEngine::getAudioContext() {
    return *mAudioContext;
}
