//
// Created by ts14ic on 12/13/17.
//

#include "DefaultEngine.h"
#include "../sdl/Sound.h"
#include "../sdl/Music.h"
#include "../json/getValue.h"
#include "../file/readFile.h"
#include <fstream>
#include <sstream>

void DefaultEngine::loadSound(const char* name, const char* filename) {
    mAssets->sound(name).load(filename);
}

void DefaultEngine::loadMusic(const char* name, const char* filename) {
    mAssets->music(name).load(filename);
}

rapidjson::Document readMediaDocument() {
    std::string mediaFile = readFile("data/common_media.json");
    rapidjson::Document doc;
    doc.Parse(mediaFile);
    return doc;
}

// todo use abstract asset classes
void DefaultEngine::loadMedia() {
    auto doc = readMediaDocument();

    auto texturesMap = getValue<rapidjson::Value::ConstObject>(doc, "/textures");
    for(const auto& entry : texturesMap) {
        mAssets->loadTexture(getValue<const char*>(entry.name, ""), getValue<const char*>(entry.value, ""));
    }

    auto soundsMap = getValue<rapidjson::Value::ConstObject>(doc, "/sounds");
    for(const auto& entry : soundsMap) {
        loadSound(getValue<const char*>(entry.name, ""), getValue<const char*>(entry.value, ""));
    }

    auto musicMap = getValue<rapidjson::Value::ConstObject>(doc, "/music");
    for(const auto& entry : musicMap) {
        loadMusic(getValue<const char*>(entry.name, ""), getValue<const char*>(entry.value, ""));
    }
}
