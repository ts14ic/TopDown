//
// Created by ts14ic on 12/12/17.
//
#include "StateMoon.h"
#include "../object/WeaponBuilder.h"
#include "../json/getValue.h"
#include "../file/readFile.h"
#include <rapidjson/error/en.h>
#include <fstream>
#include <sstream>

StateMoon::FailedToParseLevelData::FailedToParseLevelData(const char* message)
        : runtime_error(message) {}

StateMoon::FailedToParseLevelData::FailedToParseLevelData(const std::string& message)
        : runtime_error(message) {}

rapidjson::Document readLevelDocument() {
    std::string levelFile = readFile("data/levels/moon.json");
    rapidjson::Document doc;
    doc.Parse(levelFile.c_str());
    return doc;
}

void StateMoon::parseLevelData() {
    auto doc = readLevelDocument();
    if(doc.HasParseError()) {
        throw FailedToParseLevelData{rapidjson::GetParseError_En(doc.GetParseError())};
    }

    auto weaponsArray = getValue<rapidjson::Value::ConstArray>(doc, "/player/weapons");

    for(const auto& weapon : weaponsArray) {
        auto builder = WeaponBuilder{getValue<const char*>(weapon, "/name")}
                .fireSounds(getValues<std::string>(weapon, "/fire_sounds"))
                .maxAmmo(getValue<int>(weapon, "/max_ammo"))
                .projectilesPerShot(getValue<int>(weapon, "/projectiles_per_shot"))
                .length(getValue<int>(weapon, "/length"))
                .projectileSpeed(getValue<int>(weapon, "/projectile_speed"))
                .projectileDamage(getValue<int>(weapon, "/projectile_damage"))
                .projectileSpread(getValue<int>(weapon, "/projectile_spread"))
                .fireCooldown(getValue<unsigned>(weapon, "/fire_cooldown"))
                .reloadCooldown(getValue<unsigned>(weapon, "/reload_cooldown"));
        mPlayer.addWeapon(builder.build());
    }
}
