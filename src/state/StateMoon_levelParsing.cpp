//
// Created by ts14ic on 12/12/17.
//
#include "StateMoon.h"
#include "../object/WeaponBuilder.h"
#include "../json/getValue.h"
#include <fstream>
#include <sstream>

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

void StateMoon::parseLevelData() {
    auto doc = readLevelDocument();

    auto weaponsArray = getValue<rapidjson::Value::ConstArray>(doc, "/player/weapons");

    for(const auto& weapon : weaponsArray) {
        auto soundsArray = getValue<rapidjson::Value::ConstArray>(weapon, "/fire_sounds");
        std::vector<std::string> fireSounds;
        for(const auto& sound : soundsArray) {
            fireSounds.emplace_back(getValue<const char*>(sound, ""));
        }

        auto builder = WeaponBuilder{getValue<const char*>(weapon, "/name")}
                .maxAmmo(getValue<int>(weapon, "/max_ammo"))
                .projectilesPerShot(getValue<int>(weapon, "/projectiles_per_shot"))
                .length(getValue<int>(weapon, "/length"))
                .projectileSpeed(getValue<int>(weapon, "/projectile_speed"))
                .projectileDamage(getValue<int>(weapon, "/projectile_damage"))
                .projectileSpread(getValue<int>(weapon, "/projectile_spread"))
                .fireCooldown(getValue<unsigned>(weapon, "/fire_cooldown"))
                .reloadCooldown(getValue<unsigned>(weapon, "/reload_cooldown"))
                .fireSounds(fireSounds);
        mPlayer.addWeapon(builder.build());
    }
}
