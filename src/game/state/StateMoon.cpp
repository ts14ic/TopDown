#include "StateMoon.h"
#include <engine/geometry/maths.h>
#include <engine/log/Log.h>
#include <io/json/json.h>
#include <io/files/files.h>

StateMoon::StateMoon(Game& game)
        : _game{game},
          _background_tex{"moon_background"},
          _level_width(game.get_engine().get_graphic().get_screen_width()),
          _level_height(game.get_engine().get_graphic().get_screen_height()),
          _enemy_spawn_cooldown{} {
    get_engine().get_graphic().load_texture(_background_tex, "assets/gfx/test_bg.png");

    _enemy_spawn_cooldown.restart();

    _player_entity = create_player(/*position*/{_level_width / 2.0f, _level_height / 2.0f});

    load_control_scheme();
    parse_level_data();
}

void StateMoon::load_control_scheme(const char* control_scheme_file_name) {
    auto file = files::read_file_to_string(control_scheme_file_name);
    auto document = json::parse_json(file);

    auto read_hold_action = [&](const char* key, PlayerInput::HoldAction value) {
        _key_to_hold_action[json::get_int(document, key)] = value;
    };
    read_hold_action("/controls/hold/up", PlayerInput::HOLD_UP);
    read_hold_action("/controls/hold/left", PlayerInput::HOLD_LEFT);
    read_hold_action("/controls/hold/down", PlayerInput::HOLD_DOWN);
    read_hold_action("/controls/hold/right", PlayerInput::HOLD_RIGHT);
    read_hold_action("/controls/hold/trigger", PlayerInput::HOLD_TRIGGER);

    auto read_quick_action = [&](const char* key, PlayerInput::QuickAction value) {
        _key_to_quick_action[json::get_int(document, key)] = value;
    };
    read_quick_action("/controls/quick/0", PlayerInput::QUICK_0);
    read_quick_action("/controls/quick/1", PlayerInput::QUICK_1);
    read_quick_action("/controls/quick/2", PlayerInput::QUICK_2);
    read_quick_action("/controls/quick/3", PlayerInput::QUICK_3);
    read_quick_action("/controls/quick/4", PlayerInput::QUICK_4);
    read_quick_action("/controls/quick/5", PlayerInput::QUICK_5);
    read_quick_action("/controls/quick/6", PlayerInput::QUICK_6);
    read_quick_action("/controls/quick/7", PlayerInput::QUICK_7);
    read_quick_action("/controls/quick/8", PlayerInput::QUICK_8);
    read_quick_action("/controls/quick/9", PlayerInput::QUICK_9);
    read_quick_action("/controls/quick/next_weapon", PlayerInput::QUICK_NEXT_WEAPON);
    read_quick_action("/controls/quick/previous_weapon", PlayerInput::QUICK_PREVIOUS_WEAPON);
}

PlayerInput::HoldAction StateMoon::event_to_hold_action(const KeyboardEvent& event) const {
    auto action = _key_to_hold_action.find(event.get_key());
    return action != _key_to_hold_action.end()
            ? action->second
            : PlayerInput::HOLD_NONE;
}

PlayerInput::QuickAction StateMoon::event_to_quick_action(const KeyboardEvent& event) const {
    auto action = _key_to_quick_action.find(event.get_key());
    return action != _key_to_quick_action.end()
            ? action->second
            : PlayerInput::QUICK_NONE;
}

void StateMoon::handle_window_event(const WindowEvent& event) {
}

void StateMoon::handle_mouse_event(const MouseScrollEvent& event) {
    switch (event.get_type()) {
        case MouseScrollEvent::Type::SCROLL_UP: {
            for (auto& input : _player_inputs) {
                input.second.tap(PlayerInput::QUICK_PREVIOUS_WEAPON);
            }
            break;
        }

        case MouseScrollEvent::Type::SCROLL_DOWN: {
            for (auto& input : _player_inputs) {
                input.second.tap(PlayerInput::QUICK_NEXT_WEAPON);
            }
            break;
        }
    }
}

void StateMoon::handle_mouse_event(const MousePointEvent& event) {
    if (event.get_type() == MousePointEvent::Type::MOTION) {
        _mouse_pos = event.get_position();
    }

    switch (event.get_type()) {
        case MousePointEvent::Type::BUTTON_DOWN: {
            for (auto& input : _player_inputs) {
                input.second.press(PlayerInput::HOLD_TRIGGER);
            }
            break;
        }

        case MousePointEvent::Type::BUTTON_UP: {
            for (auto& input : _player_inputs) {
                input.second.release(PlayerInput::HOLD_TRIGGER);
            }
            break;
        }

        case MousePointEvent::Type::MOTION: {
            for (auto& input : _player_inputs) {
                input.second.move_mouse(event.get_position());
            }
            break;
        }
    }
}

void StateMoon::handle_key_event(const KeyboardEvent& event) {
    if (KeyboardEvent::is_key_down(event)) {
        PlayerInput::HoldAction hold_action = event_to_hold_action(event);
        for (auto& input : _player_inputs) {
            input.second.press(hold_action);
        }

    } else if (KeyboardEvent::is_key_up(event)) {
        PlayerInput::HoldAction hold_action = event_to_hold_action(event);
        for (auto& input : _player_inputs) {
            input.second.release(hold_action);
        }

        PlayerInput::QuickAction quick_action = event_to_quick_action(event);
        for (auto& input : _player_inputs) {
            input.second.tap(quick_action);
        }
    }
}

void StateMoon::restrict_position_to_level_area(Entity entity) {
    auto& transform = _transforms[entity];

    if (transform.position.x < 0) {
        transform.position.x = 0;

    } else if (transform.position.x > _level_width) {
        transform.position.x = _level_width;

    }

    if (transform.position.y < 0) {
        transform.position.y = 0;

    } else if (transform.position.y > _level_height) {
        transform.position.y = _level_height;

    }
}

void StateMoon::remove_entity(Entity entity) {
    _transforms.erase(entity);
    _speeds.erase(entity);
    _weapon_inventories.erase(entity);
    _player_inputs.erase(entity);
    _vitality.erase(entity);
    _sprites.erase(entity);
    _zombie_ais.erase(entity);
    _melee_damages.erase(entity);
    _damage_cooldowns.erase(entity);
    _wolf_ais.erase(entity);

    _bullet_entities.erase(entity);
}

Entity StateMoon::create_werewolf(const Point2d<float>& position) {
    Entity entity = _entity_factory.create_entity();

    _transforms[entity] = Transform{position, /*rotation*/0.0f, /*radius*/25.0f};
    _speeds[entity] = Speed{2.5f};
    _vitality[entity] = Vitality{30};
    _sprites[entity] = Sprite{animation::WOLF_MOVING};
    _wolf_ais[entity] = WolfAi{};

    return entity;
}

Entity StateMoon::create_player(Point2d<float> position) {
    Entity entity = _entity_factory.create_entity();

    _transforms[entity] = Transform{position, /*rotation*/0.0f, /*radius*/30.0f};
    _speeds[entity] = Speed{};
    _weapon_inventories[entity] = WeaponInventory{};
    _player_inputs[entity] = PlayerInput{};
    _vitality[entity] = Vitality{100};
    _damage_cooldowns[entity] = Timer{};
    _sprites[entity] = Sprite{animation::PLAYER_HANDS};

    return entity;
}

Entity StateMoon::create_bullet(const Transform& origin, const WeaponInventory& inventory) {
    Entity entity = _entity_factory.create_entity();

    const auto& weapon = inventory.get_selected();
    auto half_of_projectile_spread = weapon.get_projectile_spread() / 2;
    auto angle = origin.angle
                 + get_engine().get_random().get_float(-half_of_projectile_spread, half_of_projectile_spread);
    _transforms[entity] = Transform{
            make_point(
                    origin.position.x + math::cartesian_cos(angle) * weapon.get_length(),
                    origin.position.y + math::cartesian_sin(angle) * weapon.get_length()
            ),
            angle,
            /*radius*/2.0f
    };
    _melee_damages[entity] = weapon.get_projectile_damage();
    _speeds[entity] = Speed{weapon.get_projectile_speed()};
    _sprites[entity] = Sprite{animation::BULLET};

    _bullet_entities.insert(entity);

    return entity;
}

Entity StateMoon::create_zombie(Point2d<float> position) {
    Entity entity = _entity_factory.create_entity();

    _zombie_ais[entity] = ZombieAi{};
    _transforms[entity] = Transform{position, /*rotation*/0.0f, /*radius*/25.0f};
    _vitality[entity] = Vitality{50};
    _speeds[entity] = Speed{1.7f};
    _sprites[entity] = Sprite{animation::ZOMBIE_MOVING};
    _melee_damages[entity] = 15;

    Log::d("zombie %d created, %d total", entity, _zombie_ais.size());
    return entity;
}

void StateMoon::handle_logic() {
    Random& random = get_engine().get_random();

    if (_enemy_spawn_cooldown.ticks_passed_since_start(50) &&
        (_zombie_ais.size() + _wolf_ais.size() < 7)) {
        auto position = point_cast<float>(make_random_point());
        if (!random.get_bool()) {
            create_zombie(position);
        } else {
            create_werewolf(position);
        }

        _enemy_spawn_cooldown.restart();
    }

    handle_player_logic();
    handle_bullet_logic();
    handle_zombie_logic();
    handle_werewolf_logic();

    restrict_position_to_level_area(_player_entity);

    if (is_player_dead(_player_entity)) {
        _game.request_state_change(StateId::INTRO);
    }
}

bool StateMoon::is_player_dead(Entity entity) {
    return _vitality[entity].current_hp <= 0;
}

void StateMoon::handle_player_logic() {
    if (_player_inputs[_player_entity].mouse_moved()) {
        auto& player_position = _transforms[_player_entity].position;
        const auto& mouse_position = _player_inputs[_player_entity].pop_mouse_position();
        _transforms[_player_entity].angle = math::get_cartesian_angle(player_position, mouse_position);
    }

    player_handle_weapon_selection(_player_entity);

    // TODO Make the timer store a pointer to clock
    // TODO AFTER Move the condition inside the getter
    _speeds[_player_entity].max_speed = _damage_cooldowns[_player_entity].ticks_passed_since_start(500)
            ? 2.3f
            : 1.0f;

    player_update_speeds();

    gameobject_default_move(_player_entity);

    // TODO don't try to reload on every frame
    _weapon_inventories[_player_entity].try_reload_selected();

    if (_player_inputs[_player_entity].is_held(PlayerInput::HOLD_TRIGGER)) {
        auto projectiles_shot = _weapon_inventories[_player_entity].fire_from_selected(
                get_engine(),
                _transforms[_player_entity]
        );
        for (int i = 0; i < projectiles_shot; ++i) {
            create_bullet(_transforms[_player_entity], _weapon_inventories[_player_entity]);
        }
    }
}

void StateMoon::player_update_speeds() {
    // TODO extract speed calculations to share between classes
    int direction_x = _player_inputs[_player_entity].is_held(PlayerInput::HOLD_RIGHT)
                      - _player_inputs[_player_entity].is_held(PlayerInput::HOLD_LEFT);
    int direction_y = _player_inputs[_player_entity].is_held(PlayerInput::HOLD_DOWN)
                      - _player_inputs[_player_entity].is_held(PlayerInput::HOLD_UP);

    if (direction_x != 0 || direction_y != 0) {
        auto movement_angle = math::get_radian_angle(make_point(0, 0), make_point(direction_x, direction_y));

        _speeds[_player_entity].current_speed = {
                math::radian_cos(movement_angle) * _speeds[_player_entity].max_speed,
                math::radian_sin(movement_angle) * _speeds[_player_entity].max_speed
        };
    } else {
        _speeds[_player_entity].current_speed = {0.0f, 0.0f};
    }
}

void StateMoon::player_handle_weapon_selection(Entity entity) {
    while (_player_inputs[_player_entity].has_quick_actions()) {
        auto action = _player_inputs[_player_entity].pop_quick_action();
        if (action == PlayerInput::QUICK_NEXT_WEAPON) {
            _weapon_inventories[entity].select_next();

        } else if (action == PlayerInput::QUICK_PREVIOUS_WEAPON) {
            _weapon_inventories[entity].select_previous();

        } else if (PlayerInput::is_digit(action)) {
            _weapon_inventories[entity].select_by_index(PlayerInput::to_digit(action));

        }
    }

    const auto& selected_weapon_name = _weapon_inventories[entity].get_selected_name();
    const animation::Animation* animation = nullptr;
    if (selected_weapon_name == "hands") {
        animation = &animation::PLAYER_HANDS;

    } else if (selected_weapon_name == "pistol") {
        animation = &animation::PLAYER_PISTOL;

    } else if (selected_weapon_name == "shotgun") {
        animation = &animation::PLAYER_SHOTGUN;

    } else if (selected_weapon_name == "uzi") {
        animation = &animation::PLAYER_UZI;

    } else if (selected_weapon_name == "aura") {
        animation = &animation::PLAYER_AURA;

    } else {
        assert(animation != nullptr && "weapon has no sprite attached");
        animation = &animation::PLAYER_HANDS;
    }
    _sprites[entity].set_state(*animation);
}

void StateMoon::handle_bullet_logic() {
    auto& random = get_engine().get_random();

    std::vector<Entity> destroyed_bullets;
    for (auto bullet_entity : _bullet_entities) {
        Transform transform = _transforms[bullet_entity];
        Speed speed = _speeds[bullet_entity];
        auto bullet_damage = _melee_damages[bullet_entity];

        // TODO extract speed setting
        speed.current_speed = {
                math::cartesian_cos(transform.angle) * speed.max_speed,
                math::cartesian_sin(transform.angle) * speed.max_speed
        };
        transform.position = {
                transform.position.x + speed.current_speed.x,
                transform.position.y + speed.current_speed.y
        };

        if (position_out_of_level_area(transform.position)) {
            destroyed_bullets.push_back(bullet_entity);
            continue;
        }

        for (auto& zombie : _zombie_ais) {
            auto entity = zombie.first;

            if (circles_collide(transform.get_circle(), _transforms[entity].get_circle()) &&
                _vitality[entity].current_hp > 0) {
                zombie_take_damage(entity, bullet_damage);
                destroyed_bullets.push_back(bullet_entity);
                continue;
            }
        }
        for (auto& werewolf : _wolf_ais) {
            auto entity = werewolf.first;

            if (circles_collide(transform.get_circle(), _transforms[entity].get_circle())
                && _vitality[entity].current_hp > 0) {
                werewolf_take_damage(entity, bullet_damage);
                Log::d("werewolf takes %d damage, bullet destroyed", bullet_damage);
                destroyed_bullets.push_back(bullet_entity);
                continue;
            }
            if (math::get_distance(transform.position, _transforms[entity].position) < 50) {
                werewolf_teleport(entity, random);
            }
        }

        _speeds[bullet_entity].current_speed = speed.current_speed;
        _transforms[bullet_entity].position = transform.position;
    }
    for (auto entity : destroyed_bullets) {
        remove_entity(entity);
    }
}

void StateMoon::werewolf_take_damage(Entity entity, int damage_dealt) {
    if (_wolf_ais[entity].is_teleporting()) {
        damage_dealt /= 2;
    }

    if (damage_dealt > 0) _vitality[entity].current_hp -= damage_dealt;
    if (_vitality[entity].current_hp <= 0 && !_wolf_ais[entity].is_dying()) {
        _wolf_ais[entity].set_state(WolfAi::AI_DYING);
        _sprites[entity].set_state(animation::WOLF_DYING);
    }
}

void StateMoon::werewolf_teleport(Entity entity, const Random& random) {
    if (_wolf_ais[entity].is_dying()) {
        return;
    }

    if (!_wolf_ais[entity].is_teleporting() && _wolf_ais[entity].can_teleport()) {
        _transforms[entity].position = make_point(
                _transforms[entity].position.x + random.get_int(-150, 150),
                _transforms[entity].position.y + random.get_int(-150, 150)
        );
        _wolf_ais[entity].set_state(WolfAi::AI_TELEPORTING);
        _wolf_ais[entity].teleport_restart();
        _sprites[entity].set_state(animation::WOLF_TELEPORT);
    }
}

void StateMoon::zombie_take_damage(Entity entity, int damage_dealt) {
    if (damage_dealt > 0) {
        auto previous_health = _vitality[entity].current_hp;
        _vitality[entity].current_hp -= damage_dealt;
        Log::d("zombie takes damage, health at: [%d/%d]", _vitality[entity].current_hp, previous_health);
    }

    if (_vitality[entity].current_hp <= 0 && !_zombie_ais[entity].is_dying()) {
        _zombie_ais[entity].set_state(ZombieAi::AI_DYING);
        _sprites[entity].set_state(animation::ZOMBIE_DYING);
    }
}

void StateMoon::handle_zombie_logic() {
    std::vector<Entity> dead_entities;
    for (auto& entry : _zombie_ais) {
        auto entity = entry.first;
        zombie_set_target(entity, _transforms[_player_entity].position);
        zombie_handle_logic(entity);

        if (circles_collide(_transforms[entity].get_circle(), _transforms[_player_entity].get_circle())) {
            // TODO: Don't depend on animation
            int damage;
            if (_zombie_ais[entity].is_attacking() && _sprites[entity].is_last_frame()) {
                damage = _melee_damages[entity];
            } else {
                damage = 0;
            }
            player_take_damage(_player_entity, damage);
        }

        if (zombie_is_dead(entity)) {
            dead_entities.push_back(entity);
        }
    }

    for (auto dead_entity : dead_entities) {
        remove_entity(dead_entity);
        Log::d("zombie %d removed, %d total", dead_entity, _zombie_ais.size());
    }
}

void StateMoon::player_take_damage(Entity entity, int damage_dealt) {
    if (damage_dealt > 0 && _damage_cooldowns[_player_entity].ticks_passed_since_start(200)) {
        _vitality[entity].current_hp -= damage_dealt;
        _damage_cooldowns[entity].restart();
    }
}

void StateMoon::zombie_set_target(Entity entity, Point2d<float> position) {
    if (_zombie_ais[entity].is_dying()) {
        return;
    }

    _transforms[entity].angle = math::get_cartesian_angle(_transforms[entity].position, position);

    auto dist = math::get_distance(_transforms[entity].position, position);
    if (dist > _transforms[entity].get_circle().get_radius() * 1.7f) {
        if (!_zombie_ais[entity].is_moving()) {
            _zombie_ais[entity].set_state(ZombieAi::AI_MOVING);
            _sprites[entity].set_state(animation::ZOMBIE_MOVING);
        }
    } else if (!_zombie_ais[entity].is_attacking()) {
        _zombie_ais[entity].set_state(ZombieAi::AI_ATTACKING);
        _sprites[entity].set_state(animation::ZOMBIE_ATTACKING);
    }
}

void StateMoon::zombie_handle_logic(Entity entity) {
    if (_zombie_ais[entity].is_dying()) {
        _speeds[entity].current_speed = {0.0f, 0.0f};
        return;
    }

    if (_zombie_ais[entity].is_moving()) {
        // TODO extract speed setting
        auto movement_angle = _transforms[entity].angle;

        _speeds[entity].current_speed = {
                math::cartesian_cos(movement_angle) * _speeds[entity].max_speed,
                math::cartesian_sin(movement_angle) * _speeds[entity].max_speed
        };
        gameobject_default_move(entity);
    } else {
        _speeds[entity].current_speed = {0.0f, 0.0f};
    }
}

void StateMoon::gameobject_default_move(Entity entity) {
    _transforms[entity].position = {
            _transforms[entity].position.x + _speeds[entity].current_speed.x,
            _transforms[entity].position.y + _speeds[entity].current_speed.y
    };
}

bool StateMoon::zombie_is_dead(Entity entity) {
    // TODO: Don't depend on animation
    return _zombie_ais[entity].is_dying() && _sprites[entity].is_animation_ended();
}

void StateMoon::handle_werewolf_logic() {
    std::vector<Entity> dead_entities;
    for (auto& entry : _wolf_ais) {
        auto entity = entry.first;

        werewolf_set_target(entity, _transforms[_player_entity].position);
        werewolf_handle_logic(entity);

        if (circles_collide(_transforms[entity].get_circle(), _transforms[_player_entity].get_circle())) {
            int damage;
            if (_wolf_ais[entity].is_attacking() && _wolf_ais[entity].can_deal_damage()) {
                damage = 10;

            } else {
                damage = 0;

            }
            player_take_damage(_player_entity, damage);
        }

        if (_vitality[entity].current_hp <= 0 && _sprites[entity].is_animation_ended()) {
            dead_entities.push_back(entity);
        }
    }
    for (auto entity : dead_entities) {
        remove_entity(entity);
    }
}

void StateMoon::werewolf_set_target(Entity entity, const Point2d<float>& position) {
    if (_wolf_ais[entity].is_dying()) {
        return;
    }

    if (_wolf_ais[entity].is_teleporting() && !_wolf_ais[entity].teleport_finished()) {
        return;
    }

    _transforms[entity].angle = math::get_cartesian_angle(_transforms[entity].position, position);

    auto dist = math::get_distance(_transforms[entity].position, position);
    if (dist > _transforms[entity].get_circle().get_radius() * 1.7f) {
        if (!_wolf_ais[entity].is_moving()) {
            _wolf_ais[entity].set_state(WolfAi::AI_MOVING);
            _sprites[entity].set_state(animation::WOLF_MOVING);
        }
    } else if (!_wolf_ais[entity].is_attacking()) {
        _wolf_ais[entity].set_state(WolfAi::AI_ATTACKING);
        _sprites[entity].set_state(animation::WOLF_ATTACKING);
    }
}

void StateMoon::werewolf_handle_logic(Entity entity) {
    if (_wolf_ais[entity].is_dying()) {
        _speeds[entity].current_speed = {0.0f, 0.0f};
        return;
    }

    if (_wolf_ais[entity].is_moving()) {
        // TODO extract speed setting
        auto movement_angle = _transforms[entity].angle;

        _speeds[entity].current_speed = {
                math::cartesian_cos(movement_angle) * _speeds[entity].max_speed,
                math::cartesian_sin(movement_angle) * _speeds[entity].max_speed
        };
        gameobject_default_move(entity);
    } else {
        _speeds[entity].current_speed = {0.0f, 0.0f};
    }

    if (_wolf_ais[entity].is_attacking() && _wolf_ais[entity].must_reset_attack()) {
        _wolf_ais[entity].restart_attack();
    }
}

bool StateMoon::position_out_of_level_area(Point2d<float> position) const {
    return (position.x > _level_width) || (position.x < 0) ||
           (position.y > _level_height) || (position.y < 0);
}

Point2d<int> StateMoon::make_random_point() const {
    Random& random = get_engine().get_random();
    if (!random.get_bool()) {
        return make_point(
                random.get_int(0, _level_width),
                random.get_int(0, 1) * _level_height
        );
    } else {
        return make_point(
                random.get_int(0, 1) * _level_width,
                random.get_int(0, _level_height)
        );
    }
}

void StateMoon::handle_render(float milliseconds_passed, float milliseconds_per_frame) {
    float frames_passed = milliseconds_passed / milliseconds_per_frame;
    auto& engine = get_engine();
    auto& graphic = engine.get_graphic();
    graphic.clear_screen();

    auto& audio = engine.get_audio();
    audio.play_music("weather");

    graphic.render_texture(_background_tex, make_point(0, 0));

    for (auto& entry : _sprites) {
        Entity entity = entry.first;
        auto& sprite = entry.second;

        gameobject_handle_render(/*entity*/entity, frames_passed);
        sprite.update();
    }
    for (auto& vitality : _vitality) {
        // TODO: check for sprite presence
        // TODO: what color to draw health with?
        gameobject_handle_render_health(/*entity*/vitality.first, Color{0x7f, 0, 0, 0xff}, frames_passed);
    }

    for (auto& entry : _zombie_ais) {
        auto entity = entry.first;
        zombie_handle_audio(entity);
    }

    for (auto& entry : _wolf_ais) {
        auto entity = entry.first;
        werewolf_handle_audio(entity, audio);
    }

    render_crosshair(frames_passed);

    graphic.refresh_screen();
}

void StateMoon::werewolf_handle_audio(Entity entity, Audio& audio) {
    if (_wolf_ais[entity].is_attacking()) {
        // FIXME: Animation has attack points in 3 and 7 frames, not only last
        if (_sprites[entity].is_last_frame()) {
            audio.play_sound("wolf_attack");
        }

    } else if (_wolf_ais[entity].is_teleporting()) {
        if (_sprites[entity].is_last_frame()) {
            audio.play_sound("wolf_teleport");
        }

    }
}

void StateMoon::zombie_handle_audio(Entity entity) {
    // TODO: Don't depend on animation
    if (_zombie_ais[entity].is_attacking() && _sprites[entity].is_last_frame()) {
        get_engine().get_audio().play_sound("zombie_attack");
    }
}

void StateMoon::gameobject_handle_render(Entity entity, float frames_count) {
    auto texture = get_engine().get_graphic().get_texture(_sprites[entity].get_tex_name());

    auto point = make_point(
            _transforms[entity].position.x - texture.get_size().get_width() / 2.f,
            _transforms[entity].position.y - texture.get_size().get_height() / 2.f
    );
    point.x += _speeds[entity].current_speed.x * frames_count;
    point.y += _speeds[entity].current_speed.y * frames_count;

    get_engine().get_graphic().render_texture(
            texture.get_name(),
            point_cast<int>(point),
            _transforms[entity].angle
    );
}

void StateMoon::gameobject_handle_render_health(Entity entity, Color color, float frames_count) {
    if (_vitality[entity].current_hp > 0) {
        Box health_box;

        health_box.set_size(50.f * _vitality[entity].current_hp / _vitality[entity].default_hp, 5.f);
        health_box.set_left_top(
                _transforms[entity].position.x - health_box.get_width() / 2 +
                _speeds[entity].current_speed.x * frames_count,
                _transforms[entity].position.y - _transforms[entity].get_circle().get_radius() +
                _speeds[entity].current_speed.y * frames_count
        );

        get_engine().get_graphic().render_box(health_box, color);
    }
}

void StateMoon::render_crosshair(float frames_count) {
    Graphic& graphic = get_engine().get_graphic();

    auto texture = graphic.get_texture(_weapon_inventories[_player_entity].is_selected_reloading()
            ? "reload"
            : "crosshair");
    auto render_point = make_point(
            _mouse_pos.x - texture.get_size().get_width() / 2,
            _mouse_pos.y - texture.get_size().get_height() / 2
    );

    _crosshair_angle += 5.f * frames_count;
    if (_crosshair_angle > 360.f) {
        _crosshair_angle = 5.f;
    }

    graphic.render_texture(texture.get_name(), render_point, _crosshair_angle);
}

void StateMoon::parse_level_data() {
    using namespace json;

    auto document = parse_json(files::read_file_to_string("data/levels/moon.json"));

    for (const auto& weapon : get_array(document, "/player/weapons")) {

        auto builder = WeaponBuilder{get_czstring(weapon, "/name")}
                .fire_sounds(get_values<std::string>(weapon, "/fire_sounds"))
                .max_ammo(get_int(weapon, "/max_ammo"))
                .projectiles_per_shot(get_int(weapon, "/projectiles_per_shot"))
                .length(get_int(weapon, "/length"))
                .projectile_speed(get_int(weapon, "/projectile_speed"))
                .projectile_damage(get_int(weapon, "/projectile_damage"))
                .projectile_spread(get_int(weapon, "/projectile_spread"))
                .fire_cooldown(get_uint(weapon, "/fire_cooldown"))
                .reload_cooldown(get_uint(weapon, "/reload_cooldown"));

        _weapon_inventories[_player_entity].add(builder.build());
    }
}
