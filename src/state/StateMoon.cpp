#include "GameState.h"
#include "../sdlwrap.h"
#include "../engine/RenderContext.h"
#include "../engine/Engine.h"
#include "StateMoon.h"
#include "../object/Zombie.h"
#include "../object/Werewolf.h"
#include "../object/Bullet.h"
#include "../sound/Music.h"
#include <algorithm>
#include <ctime>

StateMoon::StateMoon(Engine& engine)
        : _texBackground(engine.getRenderSystem(), "assets/gfx/test_bg.png"),
          _pl(screenWidth() / 2, screenHeight() / 2) {
    std::srand(std::time(nullptr));

    zombies().clear();
    werewolves().clear();
    _mobSpawner.start();
}

void StateMoon::handle_events(Engine& engine) {
    auto& input = engine.getInputSystem();

    while(SDL_PollEvent(&input.getInputEvent())) {

        _pl.handle_events(input);

        switch(input.getInputEvent().type) {
            case SDL_QUIT:
                engine.requestStateChange(GState::exit);
                break;

            default:;
        }
    }
}

void StateMoon::restrict_pos(GameObject& o) {
    if(o.x() < 0) o.x(0);
    else if(o.x() > _levelWidth) o.x(_levelWidth);

    if(o.y() < 0) o.y(0);
    else if(o.y() > _levelHeight) o.y(_levelHeight);
}

void StateMoon::handle_logic(Engine& engine) {
    if(_mobSpawner.passed(500) && (zombies().size() + werewolves().size() < 7)) {
        if(zombies().size() < 7) {
            int border = std::rand() % 2;
            if(border == 0) {
                int lx = std::rand() % _levelWidth;
                int ly = std::rand() % 2 * _levelHeight;
                zombies().emplace_back(lx, ly);
            } else {
                int lx = std::rand() % 2 * _levelWidth;
                int ly = std::rand() % _levelHeight;
                zombies().emplace_back(lx, ly);
            }
        }

        if(werewolves().size() < 7) {
            int border = std::rand() % 2;
            if(border == 0) {
                int lx = std::rand() % _levelWidth;
                int ly = std::rand() % 2 * _levelHeight;
                werewolves().emplace_back(lx, ly);
            } else {
                int lx = std::rand() % 2 * _levelWidth;
                int ly = std::rand() % _levelHeight;
                werewolves().emplace_back(lx, ly);
            }
        }

        _mobSpawner.start();
    }

    _pl.handle_logic();

    // process bullet moving and collisions
    auto removeFrom = std::remove_if(bullets().begin(), bullets().end(), [](Bullet& b) {
        b.handle_logic();

        if((b.x() > screenWidth()) || (b.x() < 0) ||
           (b.y() > screenHeight()) || (b.y() < 0)) {
            return true;
        }

        for(auto& z : zombies()) {
            if(objectsCollide(b, z) && z.hp() > 0) {
                z.damage(b.dmg());
                return true;
            }
        }
        for(auto& w : werewolves()) {
            if(objectsCollide(b, w) && w.hp() > 0) {
                w.damage(b.dmg());
                return true;
            }
            if(get_distance(b.x(), b.y(), w.x(), w.y()) < 50) {
                w.teleport();
            }
        }

        return false;
    });
    bullets().erase(removeFrom, bullets().end());

    zombies().erase(std::remove_if(zombies().begin(), zombies().end(), [this](Zombie& z) {
        z.set_target(_pl.x(), _pl.y());
        z.handle_logic();

        if(objectsCollide(z, _pl)) {
            _pl.damage(z.dmg());
        }

        return z.dead();
    }), zombies().end());

    werewolves().erase(std::remove_if(werewolves().begin(), werewolves().end(), [this](Werewolf& w) {
        w.set_target(_pl.x(), _pl.y());
        w.handle_logic();

        if(objectsCollide(w, _pl)) {
            _pl.damage(w.dmg());
        }

        return w.dead();
    }), werewolves().end());

    restrict_pos(_pl);
    if(_pl.dead()) engine.requestStateChange(GState::intro);
}

static void render_crosshair(RenderContext& engine, Player const& pl) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    mx -= textures("crosshair").w() / 2;
    my -= textures("crosshair").h() / 2;
    static float angle = 0.f;
    angle += 5.f;
    if(angle > 360.f) angle = 5.f;
    if(pl.reloading()) {
        textures("reload").render(engine, mx, my, angle);
    } else {
        textures("crosshair").render(engine, mx, my, angle);
    }
}

void StateMoon::handle_render(Engine& engine) {
    auto& render = engine.getRenderSystem();

    SDL_RenderClear(render.getRenderer());

    music("weather").play();

    _texBackground.render(render, 0, 0);

    _pl.handle_render(render);
    for(auto& z : zombies()) {
        z.handle_render(render);
    }
    for(auto& w : werewolves()) {
        w.handle_render(render);
    }
    for(auto& b : bullets()) {
        b.handle_render(render);
    }

    render_crosshair(render, _pl);

    SDL_RenderPresent(render.getRenderer());
}
