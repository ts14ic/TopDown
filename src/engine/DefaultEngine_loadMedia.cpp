//
// Created by ts14ic on 12/13/17.
//

#include "DefaultEngine.h"
#include "../sound/Sound.h"
#include "../sound/Music.h"
#include "../texture/Texture.h"
#include "../json/getValue.h"
#include <fstream>
#include <sstream>
#include <iostream>

void DefaultEngine::loadTexture(const char* name, const char* filename) {
    mAssets->texture(name).load(getRenderContext(), filename);
}

void DefaultEngine::loadSound(const char* name, const char* filename) {
    mAssets->sound(name).load(filename);
}

void DefaultEngine::loadMusic(const char* name, const char* filename) {
    mAssets->music(name).load(filename);
}

// todo extract these two common reading functions
std::string readMediaFile() {
    std::ifstream mediaFile{"data/common_media.json"};
    if(!mediaFile) {
        throw std::runtime_error{"Failed to open data/common_media.json"};
    }
    std::stringstream buffer;
    buffer << mediaFile.rdbuf();
    return buffer.str();
}

rapidjson::Document readMediaDocument() {
    std::string mediaFile = readMediaFile();
    rapidjson::Document doc;
    doc.Parse(mediaFile);
    return doc;
}

// todo use abstract asset classes
void DefaultEngine::loadMedia() {
    auto doc = readMediaDocument();

    auto texturesMap = getValue<rapidjson::Value::ConstObject>(doc, "/textures");
    for(const auto& entry : texturesMap) {
        loadTexture(getValue<const char*>(entry.name, ""), getValue<const char*>(entry.value, ""));
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
