#include "StateMoon.h"
#include "../../utils/math/math.h"
#include "../../engine/Engine.h"
#include "../object/Zombie.h"
#include "../object/Werewolf.h"
#include "../object/Bullet.h"
#include "../../engine/resources/Texture.h"
#include "../../engine/input/InputContext.h"
#include "../../engine/graphic/GraphicContext.h"
#include "../../engine/Random.h"
#include "../../engine/resources/Resources.h"
#include "../../engine/resources/Music.h"
#include "../../engine/input/WindowEvent.h"
#include "../../engine/input/MouseEvent.h"
#include <algorithm>
#include <ctime>

StateMoon::StateMoon(Engine& engine)
        : mEngine{engine},
          mBackgroundTexId{"moon_background"},
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

StateMoon::StateMoon(const StateMoon& other)
        : StateMoon{other.mEngine} {
}

void StateMoon::handleWindowEvent(const WindowEvent& event) {
}

void StateMoon::handleMouseEvent(const MouseEvent& event) {
    if(event.getType() == MouseEvent::Type::Motion) {
        mMouseX = static_cast<int>(event.getX());
        mMouseY = static_cast<int>(event.getY());
    }

    mPlayer.handleMouseEvent(event);
}

void StateMoon::handleKeyEvent(const KeyboardEvent& event) {
    mPlayer.handleKeyEvent(event);
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

void StateMoon::handleLogic() {
    if(mEnemySpawnCooldown.haveTicksPassedSinceStart(mEngine.getClock(), 50) &&
       (zombies().size() + werewolves().size() < 7)) {
        auto position = randomPosition(mEngine.getRandom(), _levelWidth, _levelHeight);
        int type = mEngine.getRandom().getInt(0, 1);
        if(type == 0) {
            zombies().emplace_back(position.first, position.second);
        } else {
            werewolves().emplace_back(position.first, position.second);
        }

        mEnemySpawnCooldown.restart(mEngine.getClock());
    }

    mPlayer.handle_logic(mEngine.getRandom(), mEngine.getResources(), mEngine.getAudioContext());

    const auto& clock = mEngine.getClock();
    auto& random = mEngine.getRandom();

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
                                             if(math::getDistance(b.getX(), b.getY(), w.getX(), w.getY()) < 50) {
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
        w.handleLogic(clock);

        if(objectsCollide(w, mPlayer)) {
            mPlayer.damage(clock, w.dmg());
        }

        return w.dead();
    }), werewolves().end());

    restrict_pos(mPlayer);
    if(mPlayer.dead()) mEngine.requestStateChange(GState::intro);
}

void renderCrosshair(int mouseX, int mouseY, Resources& resources, GraphicContext& graphicContext, Player const& pl,
                     float predictionRatio) {
    int x = mouseX - resources.getTexture("crosshair").getWidth() / 2;
    int y = mouseY - resources.getTexture("crosshair").getHeight() / 2;

    static float angle = 0.f;
    angle += 5.f * predictionRatio;
    if(angle > 360.f) angle = 5.f;

    graphicContext.render(resources.getTexture(pl.reloading() ? "reload" : "crosshair"), x, y, angle);
}

void StateMoon::handleRender(float predictionRatio) {
    auto& render = mEngine.getGraphicContext();
    render.clearScreen();

    auto& resources = mEngine.getResources();
    auto& audio = mEngine.getAudioContext();
    audio.playMusic(resources.getMusic("weather"));

    render.render(resources.getTexture(mBackgroundTexId), 0, 0);

    mPlayer.handleRender(resources, render, predictionRatio);

    for(auto& z : zombies()) {
        z.handleRender(resources, render, mEngine.getAudioContext(), predictionRatio);
    }

    for(auto& w : werewolves()) {
        w.handleRender(resources, render, mEngine.getAudioContext(), predictionRatio);
    }

    for(auto& b : bullets()) {
        b.handleRender(resources, render, predictionRatio);
    }

    renderCrosshair(mMouseX, mMouseY, resources, render, mPlayer, predictionRatio);

    render.refreshScreen();
}
