#include "StateMoon.h"
#include "../math/math.h"
#include "../engine/Engine.h"
#include "../object/Zombie.h"
#include "../object/Werewolf.h"
#include "../object/Bullet.h"
#include <SDL_render.h>
#include <algorithm>
#include <ctime>

StateMoon::StateMoon(Engine& engine)
        : _texBackground(engine.getRenderContext(), "assets/gfx/test_bg.png"),
          mRandomEngine{std::random_device{}()} {
    zombies().clear();
    werewolves().clear();
    _mobSpawner.restart();

    mPlayer.setPos(
            engine.getRenderContext().getScreenWidth() / 2,
            engine.getRenderContext().getScreenHeight() / 2
    );

    parseLevelData();
}

int StateMoon::randomInt() {
    return mRandomDistribution(mRandomEngine);
}

void StateMoon::handle_events(Engine& engine) {
    auto& input = engine.getInputContext();

    while(SDL_PollEvent(&input.getInputEvent())) {

        mPlayer.handle_events(input);

        switch(input.getInputEvent().type) {
            case SDL_QUIT:
                engine.requestStateChange(GState::exit);
                break;

            default:;
        }
    }
}

void StateMoon::restrict_pos(GameObject& o) {
    if(o.getX() < 0) o.setX(0);
    else if(o.getX() > _levelWidth) o.setX(_levelWidth);

    if(o.getY() < 0) o.setY(0);
    else if(o.getY() > _levelHeight) o.setY(_levelHeight);
}

void StateMoon::handle_logic(Engine& engine) {
    if(_mobSpawner.ticksHavePassed(500) && (zombies().size() + werewolves().size() < 7)) {
        if(zombies().size() < 7) {
            int border = randomInt() % 2;
            if(border == 0) {
                int lx = randomInt() % _levelWidth;
                int ly = randomInt() % 2 * _levelHeight;
                zombies().emplace_back(lx, ly);
            } else {
                int lx = randomInt() % 2 * _levelWidth;
                int ly = randomInt() % _levelHeight;
                zombies().emplace_back(lx, ly);
            }
        }

        if(werewolves().size() < 7) {
            int border = randomInt() % 2;
            if(border == 0) {
                int lx = randomInt() % _levelWidth;
                int ly = randomInt() % 2 * _levelHeight;
                werewolves().emplace_back(lx, ly);
            } else {
                int lx = randomInt() % 2 * _levelWidth;
                int ly = randomInt() % _levelHeight;
                werewolves().emplace_back(lx, ly);
            }
        }

        _mobSpawner.restart();
    }

    mPlayer.handle_logic(engine.getAssets());

    int screenWidth = engine.getRenderContext().getScreenWidth();
    int screenHeight = engine.getRenderContext().getScreenHeight();

    // process bullet moving and collisions
    auto removeFrom = std::remove_if(bullets().begin(), bullets().end(), [screenWidth, screenHeight](Bullet& b) {
        b.handle_logic();

        if((b.getX() > screenWidth) || (b.getX() < 0) ||
           (b.getY() > screenHeight) || (b.getY() < 0)) {
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
            if(getDistance(b.getX(), b.getY(), w.getX(), w.getY()) < 50) {
                w.teleport();
            }
        }

        return false;
    });
    bullets().erase(removeFrom, bullets().end());

    zombies().erase(std::remove_if(zombies().begin(), zombies().end(), [this](Zombie& z) {
        z.set_target(mPlayer.getX(), mPlayer.getY());
        z.handle_logic();

        if(objectsCollide(z, mPlayer)) {
            mPlayer.damage(z.dmg());
        }

        return z.dead();
    }), zombies().end());

    werewolves().erase(std::remove_if(werewolves().begin(), werewolves().end(), [this](Werewolf& w) {
        w.set_target(mPlayer.getX(), mPlayer.getY());
        w.handle_logic();

        if(objectsCollide(w, mPlayer)) {
            mPlayer.damage(w.dmg());
        }

        return w.dead();
    }), werewolves().end());

    restrict_pos(mPlayer);
    if(mPlayer.dead()) engine.requestStateChange(GState::intro);
}

static void render_crosshair(Assets& assets, RenderContext& renderContext, Player const& pl) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    mx -= assets.texture("crosshair").getWidth() / 2;
    my -= assets.texture("crosshair").getHeight() / 2;
    static float angle = 0.f;
    angle += 5.f;
    if(angle > 360.f) angle = 5.f;
    renderContext.render(assets.texture(pl.reloading() ? "reload" : "crosshair"), mx, my, angle);
}

void StateMoon::handle_render(Engine& engine) {
    auto& render = engine.getRenderContext();

    SDL_RenderClear(render.getRenderer());

    engine.getAssets().music("weather").play();

    engine.getRenderContext().render(_texBackground, 0, 0);

    mPlayer.handle_render(engine.getAssets(), render);
    for(auto& z : zombies()) {
        z.handle_render(engine.getAssets(), render);
    }
    for(auto& w : werewolves()) {
        w.handle_render(engine.getAssets(), render);
    }
    for(auto& b : bullets()) {
        b.handle_render(engine.getAssets(), render);
    }

    render_crosshair(engine.getAssets(), render, mPlayer);

    SDL_RenderPresent(render.getRenderer());
}
