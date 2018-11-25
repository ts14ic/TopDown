#pragma once

#include "GameState.h"
#include <game/components/Sprite.h>
#include <game/components/ZombieAi.h>
#include <game/object/Player.h>
#include <game/object/Werewolf.h>
#include <game/Game.h>
#include <game/timer/Timer.h>
#include <engine/geometry/Point2.h>
#include <cassert>

using Entity = std::size_t;

class StateMoon : public GameState {
public:
    explicit StateMoon(Game& game);

    void handle_window_event(const WindowEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_logic() override;

    void restrict_pos(GameObject&);

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

    Point2<int> make_random_point() const;

    bool position_out_of_level_area(Point2<float> position) const;

    void render_crosshair(float frames_count);

private:
    Entity create_entity() {
        // TODO: Make a proper entity id factory and class
        auto entity = _entity_counter;
        assert(_entity_counter < SIZE_MAX && "Entity pool exhausted");
        ++_entity_counter;
        return entity;
    }

    Entity create_zombie(Point2<float> position);

    void remove_zombie(Entity entity);

    void zombie_take_damage(Entity entity, int damage_dealt);

    void zombie_handle_render(Entity entity, float frames_count);

    void zombie_set_target(Entity entity, Point2<float> position);

    void zombie_handle_logic(Entity entity);

    bool zombie_is_dead(Entity entity);

    void gameobject_handle_render(Entity entity, float frames_count);

    void gameobject_handle_render_health(Entity entity, Color color, float frames_count);

    void gameobject_default_move(Entity entity);

    Game& _game;
    std::string _background_tex;
    const int _level_width;
    const int _level_height;
    Point2<int> _mouse_pos;

    Player _player;
    std::vector<Bullet> _bullets;
    std::vector<Werewolf> _werewolves;
    float _crosshair_angle;

    Entity _entity_counter = 1;
    std::unordered_map<Entity, Transform> _transforms;
    std::unordered_map<Entity, Speed> _speeds;
    std::unordered_map<Entity, Hitpoints> _hitpoints;
    std::unordered_map<Entity, Sprite> _sprites;
    std::unordered_map<Entity, ZombieAi> _zombie_ais;
    std::unordered_map<Entity, int> _melee_damages;

    Timer _enemy_spawn_cooldown;
};
