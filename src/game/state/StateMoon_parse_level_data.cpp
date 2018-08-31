#include "StateMoon.h"
#include "io/json/get_value.h"
#include "io/json/parse_json.h"
#include "io/files/files.h"

void StateMoon::parse_level_data() {
    auto doc = json::parse_json(files::read_file_to_string("data/levels/moon.json"));

    using json::get_value;
    auto weapons_array = get_value<rapidjson::Value::ConstArray>(doc, "/player/weapons");

    using json::get_values;
    for(const auto& weapon : weapons_array) {
        auto builder = WeaponBuilder{get_value<const char *>(weapon, "/name")}
                .fire_sounds(get_values<std::string>(weapon, "/fire_sounds"))
                .max_ammo(get_value<int>(weapon, "/max_ammo"))
                .projectiles_per_shot(get_value<int>(weapon, "/projectiles_per_shot"))
                .length(get_value<int>(weapon, "/length"))
                .projectile_speed(get_value<int>(weapon, "/projectile_speed"))
                .projectile_damage(get_value<int>(weapon, "/projectile_damage"))
                .projectile_spread(get_value<int>(weapon, "/projectile_spread"))
                .fire_cooldown(get_value<unsigned>(weapon, "/fire_cooldown"))
                .reload_cooldown(get_value<unsigned>(weapon, "/reload_cooldown"));
        _player.addWeapon(builder.build());
    }
}
