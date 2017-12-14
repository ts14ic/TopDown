#include "StateMoon.h"
#include "../math/math.h"
#include "../engine/Engine.h"
#include "../object/Zombie.h"
#include "../object/Werewolf.h"
#include "../object/Bullet.h"
#include "../resources/Texture.h"
#include "../engine/InputContext.h"
#include "../engine/GraphicContext.h"
#include "../engine/Random.h"
#include "../resources/Resources.h"
#include "../resources/Music.h"
#include <SDL_render.h>
#include <SDL_events.h>
#include <algorithm>
#include <ctime>
#include <iostream>

StateMoon::StateMoon(Engine& engine)
        : mBackgroundTexId{"moon_background"},
          _levelWidth(engine.getGraphicContext().getScreenWidth()),
          _levelHeight(engine.getGraphicContext().getScreenHeight()),
          mEnemySpawnCooldown{} {
    engine.getResources().loadTexture(mBackgroundTexId, "assets/gfx/test_bg.png");

    zombies().clear();
    werewolves().clear();
    mEnemySpawnCooldown.restart(engine.getClock());

    mPlayer.setPos(_levelWidth / 2, _levelHeight / 2);

    parseLevelData();
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

std::pair<int, int> randomPosition(Random& random, int width, int height) {
    int border = random.getInt(0, 1);
    int lx;
    int ly;
    if(border == 0) {
        lx = random.getInt(0, width);
        ly = random.getInt(0, 1) * height;
    } else {
        lx = random.getInt(0, 1) * width;
        ly = random.getInt(0, height);
    }
    return {lx, ly};
}

void StateMoon::handle_logic(Engine& engine) {
    if(mEnemySpawnCooldown.haveTicksPassedSinceStart(engine.getClock(), 50) &&
       (zombies().size() + werewolves().size() < 7)) {
        auto position = randomPosition(engine.getRandom(), _levelWidth, _levelHeight);
        int type = engine.getRandom().getInt(0, 1);
        if(type == 0) {
            zombies().emplace_back(position.first, position.second);
        } else {
            werewolves().emplace_back(position.first, position.second);
        }

        mEnemySpawnCooldown.restart(engine.getClock());
    }

    mPlayer.handle_logic(engine.getRandom(), engine.getResources(), engine.getAudioContext());

    const auto& clock = engine.getClock();
    // todo random should be logically const
    auto& random = engine.getRandom();

    int maxWidth = _levelWidth;
    int maxHeight = _levelHeight;
    // process bullet moving and collisions
    auto removeFrom = std::remove_if(bullets().begin(), bullets().end(),
                                     [maxWidth, maxHeight, &random, &clock](Bullet& b) {
                                         b.handle_logic();

                                         if((b.getX() > maxWidth) || (b.getX() < 0) ||
                                            (b.getY() > maxHeight) || (b.getY() < 0)) {
                                             return true;
                                         }

                                         for(auto& z : zombies()) {
                                             if(objectsCollide(b, z) && z.hp() > 0) {
                                                 z.damage(clock, b.dmg());
                                                 return true;
                                             }
                                         }
                                         for(auto& w : werewolves()) {
                                             if(objectsCollide(b, w) && w.hp() > 0) {
                                                 w.damage(clock, b.dmg());
                                                 return true;
                                             }
                                             if(getDistance(b.getX(), b.getY(), w.getX(), w.getY()) < 50) {
                                                 w.teleport(clock, random);
                                             }
                                         }

                                         return false;
                                     });
    bullets().erase(removeFrom, bullets().end());

    zombies().erase(std::remove_if(zombies().begin(), zombies().end(), [this, &clock](Zombie& z) {
        z.set_target(mPlayer.getX(), mPlayer.getY());
        z.handle_logic();

        if(objectsCollide(z, mPlayer)) {
            mPlayer.damage(clock, z.dmg());
        }

        return z.dead();
    }), zombies().end());

    werewolves().erase(std::remove_if(werewolves().begin(), werewolves().end(), [this, &clock](Werewolf& w) {
        w.set_target(clock, mPlayer.getX(), mPlayer.getY(), false);
        w.handle_logic(clock);

        if(objectsCollide(w, mPlayer)) {
            mPlayer.damage(clock, w.dmg());
        }

        return w.dead();
    }), werewolves().end());

    restrict_pos(mPlayer);
    if(mPlayer.dead()) engine.requestStateChange(GState::intro);
}

static void render_crosshair(Resources& resources, GraphicContext& graphicContext, Player const& pl) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    mx -= resources.getTexture("crosshair").getWidth() / 2;
    my -= resources.getTexture("crosshair").getHeight() / 2;
    static float angle = 0.f;
    angle += 5.f;
    if(angle > 360.f) angle = 5.f;
    graphicContext.render(resources.getTexture(pl.reloading() ? "reload" : "crosshair"), mx, my, angle);
}

void StateMoon::handle_render(Engine& engine) {
    auto& render = engine.getGraphicContext();
    render.clearScreen();

    auto& resources = engine.getResources();
    auto& audio = engine.getAudioContext();
    audio.playMusic(resources.getMusic("weather"));

    render.render(resources.getTexture(mBackgroundTexId), 0, 0);

    mPlayer.handle_render(resources, render);
    for(auto& z : zombies()) {
        z.handle_render(resources, render, engine.getAudioContext());
    }
    for(auto& w : werewolves()) {
        w.handle_render(resources, render, engine.getAudioContext());
    }
    for(auto& b : bullets()) {
        b.handle_render(resources, render);
    }

    render_crosshair(resources, render, mPlayer);

    render.refreshScreen();
}
