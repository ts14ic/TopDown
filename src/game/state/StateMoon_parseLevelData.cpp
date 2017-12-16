//
// Created by ts14ic on 12/12/17.
//
#include "StateMoon.h"
#include "../object/WeaponBuilder.h"
#include "../../json/getValue.h"
#include "../../file/readFile.h"
#include "../../json/parseJson.h"

void StateMoon::parseLevelData() {
    auto doc = json::parseJson(file::readFile("data/levels/moon.json"));

    using json::getValue;
    auto weaponsArray = getValue<rapidjson::Value::ConstArray>(doc, "/player/weapons");

    using json::getValues;
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
