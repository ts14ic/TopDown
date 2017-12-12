//
// Created by ts14ic on 12/12/17.
//
#include "StateMoon.h"
#include "../object/WeaponBuilder.h"
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <fstream>
#include <sstream>

using namespace std::literals::string_literals;

using JsonValue = rapidjson::GenericValue<rapidjson::UTF8<>>;
using JsonArray = rapidjson::GenericValue<rapidjson::UTF8<>>::ConstArray;
using JsonObject = rapidjson::GenericValue<rapidjson::UTF8<>>::ConstObject;

StateMoon::FailedToParseLevelData::FailedToParseLevelData(const char* message)
        : runtime_error(message) {}

StateMoon::FailedToParseLevelData::FailedToParseLevelData(const std::string& message)
        : runtime_error(message) {}

std::string readLevelFile() {
    std::ifstream levelFile{"data/levels/moon.json"};
    if(!levelFile) {
        throw StateMoon::FailedToParseLevelData{"Failed to open data/levels/moon.json"};
    }
    std::stringstream buffer;
    buffer << levelFile.rdbuf();
    return buffer.str();
}

rapidjson::Document readLevelDocument() {
    std::string levelFile = readLevelFile();
    rapidjson::Document doc;
    doc.Parse(levelFile.c_str());
    return doc;
}

void throwError(const char* name) {
    throw StateMoon::FailedToParseLevelData{"Failed to get "s + name};
}

void checkMember(const JsonObject& value, const char* name) {
    if(!value.HasMember(name)) {
        throwError(name);
    }
}

int getInt(const JsonObject& value, const char* name) {
    checkMember(value, name);
    if(!value[name].IsInt()) {
        throwError(name);
    }
    return value[name].GetInt();
}

unsigned getUint(const JsonObject& value, const char* name) {
    checkMember(value, name);
    if(!value[name].IsUint()) {
        throwError(name);
    }
    return value[name].GetUint();
}

std::string getString(const JsonObject& value, const char* name) {
    checkMember(value, name);
    if(!value[name].IsString()) {
        throwError(name);
    }
    return value[name].GetString();
}

JsonArray getArray(const JsonObject& value, const char* name) {
    checkMember(value, name);
    if(!value[name].IsArray()) {
        throwError(name);
    }
    return value[name].GetArray();
}

std::vector<std::string> getStringVector(const JsonObject& value, const char* name) {
    std::vector<std::string> stringVector;
    for(const auto& str : getArray(value, name)) {
        if(!str.IsString()) {
            throwError(name);
        }
        stringVector.emplace_back(str.GetString());
    }
    return stringVector;
}

void StateMoon::parseLevelData() {
    auto doc = readLevelDocument();

    if(!doc.HasMember("player") || !doc["player"].IsObject()) {
        throw FailedToParseLevelData{"No player field"};
    };

    auto player = doc["player"].GetObject();

    if(!player.HasMember("weapons")) {
        return;
    }

    if(!player["weapons"].IsArray()) {
        throw FailedToParseLevelData{"Player/weapons not an array"};
    }

    auto weapons = player["weapons"].GetArray();
    for(const auto& weaponValue : weapons) {
        if(!weaponValue.IsObject()) {
            throw FailedToParseLevelData{"player/weapons/weapon not an object"};
        }
        auto weapon = weaponValue.GetObject();

        Weapon weap = WeaponBuilder{getString(weapon, "name")}
                .maxAmmo(getInt(weapon, "max_ammo"))
                .projectilesPerShot(getInt(weapon, "projectiles_per_shot"))
                .length(getInt(weapon, "length"))
                .projectileSpeed(getInt(weapon, "projectile_speed"))
                .projectileDamage(getInt(weapon, "projectile_damage"))
                .projectileSpread(getInt(weapon, "projectile_spread"))
                .fireCooldown(getUint(weapon, "fire_cooldown"))
                .reloadCooldown(getUint(weapon, "reload_cooldown"))
                .fireSounds(getStringVector(weapon, "fire_sounds"))
                .build();
        mPlayer.addWeapon(weap);
    }
}
