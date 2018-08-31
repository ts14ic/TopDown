#include "StateMoon.h"
#include "utils/json/get_value.h"
#include "utils/json/parse_json.h"
#include "utils/file/read_file_to_string.h"

void StateMoon::parse_level_data() {
    auto doc = json::parse_json(file::read_file_to_string("data/levels/moon.json"));

    using json::get_value;
    auto weaponsArray = get_value<rapidjson::Value::ConstArray>(doc, "/player/weapons");

    using json::get_values;
    for(const auto& weapon : weaponsArray) {
        auto builder = WeaponBuilder{get_value<const char *>(weapon, "/name")}
                .fire_sounds(get_values<std::string>(weapon, "/fire_sounds"))
                .max_ammo(get_value<int>(weapon, "/max_ammo"))
                .max_ammo(get_value<int>(weapon, "/projectiles_per_shot"))
                .max_ammo(get_value<int>(weapon, "/length"))
                .projectile_speed(get_value<int>(weapon, "/projectile_speed"))
                .max_ammo(get_value<int>(weapon, "/projectile_damage"))
                .projectile_speed(get_value<int>(weapon, "/projectile_spread"))
                .fire_cooldown(get_value<unsigned>(weapon, "/fire_cooldown"))
                .fire_cooldown(get_value<unsigned>(weapon, "/reload_cooldown"));
        _player.addWeapon(builder.build());
    }
}
