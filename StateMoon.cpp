#include "GameState.h"
#include "sdlwrap.h"
#include "Sound.h"
#include "GameObject.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>

StateMoon::StateMoon()
: _texBackground("gfx/test_bg.png"),
  _pl(screenWidth() / 2, screenHeight() / 2)
{
    std::srand(std::time(nullptr));
    
    zombies().clear();
    werewolves().clear();
    _mobSpawner.start();
}

void StateMoon::handle_events() {
    while(SDL_PollEvent(&gameEvent())) {
        
        _pl.handle_events();
        
        switch(gameEvent().type) {
            case SDL_QUIT:
            prepare_state(GState::exit);
            break;
            
            default:;
        }
    }
}

void StateMoon::handle_logic() {
    if(_mobSpawner.passed(500) && (zombies().size() + werewolves().size() < 7)) {
        if(zombies().size() < 7) {
            int border = std::rand() % 2;
            if(border == 0) {
                int lx = std::rand() % _levelWidth;
                int ly = std::rand() % 2 * _levelHeight;
                zombies().emplace_back(lx, ly);
            }
            else {
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
            }
            else {
                int lx = std::rand() % 2 * _levelWidth;
                int ly = std::rand() % _levelHeight;
                werewolves().emplace_back(lx, ly);
            }
        }
        
        _mobSpawner.start();
    }
    
    _pl.handle_logic();
    
    // process bullet moving and collisions
    auto removeFrom = std::remove_if(bullets().begin(), bullets().end(), [](Bullet& b){
        b.handle_logic();
        
        if((b.x() > screenWidth())  || (b.x() < 0) ||
           (b.y() > screenHeight()) || (b.y() < 0))
        {
            return true;
        }
        
        for(auto& z : zombies()) {
            if(b.collides(z) && z.hp() > 0) {
                z.damage(b.dmg());
                return true;
            }
        }
        for(auto& w : werewolves()) {
            if(b.collides(w) && w.hp() > 0) {
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
    
    zombies().erase(std::remove_if(zombies().begin(), zombies().end(), [this](Zombie& z){
        z.set_target(_pl.x(), _pl.y());
        z.handle_logic();
        
        if(z.collides(_pl)) {
            _pl.damage(z.dmg());
        }
        
        return z.dead();
    }), zombies().end());
    
    werewolves().erase(std::remove_if(werewolves().begin(), werewolves().end(), [this](Werewolf& w){
        w.set_target(_pl.x(), _pl.y());
        w.handle_logic();
        
        if(w.collides(_pl)) {
            _pl.damage(w.dmg());
        }
        
        return w.dead();
    }), werewolves().end());
    
    for(auto& b : bullets()) {
        b.handle_logic();
    }
    if(_pl.dead()) prepare_state(GState::intro);
}

void StateMoon::handle_render() {
    SDL_RenderClear(renderer());

    music("weather").play();
    
    _texBackground.render(0, 0);
    
    _pl.handle_render();
    for(auto& z : zombies()) {
        z.handle_render();
    }
    for(auto& w : werewolves()) {
        w.handle_render();
    }
    for(auto& b : bullets()) {
        b.handle_render();
    }
    
    SDL_RenderPresent(renderer());
}
