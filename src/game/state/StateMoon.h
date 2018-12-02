#pragma once

#include "GameState.h"
#include <game/components/EntityFactory.h>
#include <game/components/DebugInfo.h>
#include <game/components/Sprite.h>
#include <game/components/ZombieAi.h>
#include <game/components/PlayerInput.h>
#include <game/components/Speed.h>
#include <game/components/WeaponInventory.h>
#include <game/components/WolfAi.h>
#include <game/components/Vitality.h>
#include <game/Game.h>
#include <game/timer/Timer.h>
#include <engine/geometry/Point2d.h>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

class StateMoon : public GameState {
public:
    explicit StateMoon(Game& game);

    void handle_window_event(const WindowEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_logic() override;

    void restrict_position_to_level_area(Entity entity);

    void handle_render(float milliseconds_passed, float milliseconds_per_frame) override;

private:
    Engine& get_engine() const {
        return _game.get_engine();
    }

    void handle_player_logic();

    void handle_bullet_logic();

    void handle_zombie_logic();

    void handle_werewolf_logic();

    void parse_level_data();

    Point2d<int> make_random_point() const;

    bool position_out_of_level_area(Point2d<float> position) const;

    void render_crosshair(float frames_count);

    void remove_entity(Entity entity);

    Entity create_bullet(const Transform& origin, const WeaponInventory& inventory);

    Entity create_werewolf(const Point2d<float>& position);

    void werewolf_set_target(Entity entity, const Point2d<float>& position);

    void werewolf_handle_logic(Entity entity);

    void werewolf_take_damage(Entity entity, int damage_dealt);

    void werewolf_teleport(Entity entity, const Random& random);

    void werewolf_handle_audio(Entity entity, Audio& audio);

    Entity create_player(Point2d<float> position);

    void player_handle_weapon_selection(Entity entity);

    void player_take_damage(Entity entity, int damage_dealt);

    void player_update_speeds();

    Entity create_zombie(Point2d<float> position);

    void zombie_take_damage(Entity entity, int damage_dealt);

    void zombie_handle_audio(Entity entity);

    void zombie_set_target(Entity entity, Point2d<float> position);

    void zombie_handle_logic(Entity entity);

    bool zombie_is_dead(Entity entity);

    void gameobject_handle_render(Entity entity, float frames_count);

    void gameobject_handle_render_health(Entity entity, Color color, float frames_count);

    void gameobject_update_speeds(Entity entity);

    void gameobject_default_move(Entity entity);

    void gameobject_reset_speed(Entity entity);

    void load_control_scheme(const char* control_scheme_file_name = "data/config.json");

    PlayerInput::HoldAction event_to_hold_action(const KeyboardEvent& event) const;

    PlayerInput::QuickAction event_to_quick_action(const KeyboardEvent& event) const;

private:
    Game& _game;
    std::string _background_tex;
    const int _level_width;
    const int _level_height;
    Point2d<int> _mouse_pos;

    float _crosshair_angle;

    EntityFactory _entity_factory;

    Entity _player_entity;
    std::unordered_set<Entity> _bullet_entities;

    std::unordered_map<Entity, DebugInfo> _debug_infos;
    std::unordered_map<Entity, Transform> _transforms;
    std::unordered_map<Entity, Speed> _speeds;
    std::unordered_map<Entity, WeaponInventory> _weapon_inventories;
    std::unordered_map<Entity, PlayerInput> _player_inputs;
    std::unordered_map<Entity, Vitality> _vitality;
    std::unordered_map<Entity, Sprite> _sprites;
    std::unordered_map<Entity, ZombieAi> _zombie_ais;
    std::unordered_map<Entity, int> _melee_damages;
    std::unordered_map<Entity, Timer> _damage_cooldowns;
    std::unordered_map<Entity, WolfAi> _wolf_ais;

    std::unordered_map<int, PlayerInput::HoldAction> _key_to_hold_action;
    std::unordered_map<int, PlayerInput::QuickAction> _key_to_quick_action;

    Timer _enemy_spawn_cooldown;
};
