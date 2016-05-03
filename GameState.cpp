#include "GameState.h"
#include <SDL_events.h>

template <class T>
using uptr = std::unique_ptr<T>;

SDL_Event& gameEvent() {
    static SDL_Event ret;
    return ret;
}

uptr<GameState>& currentState() {
    static uptr<GameState> ret;
    return ret;
}

GState& currentStateID() {
    static GState ret = GState::null;
    return ret;
}

GState& nextStateID() {
    static GState ret = GState::null;
    return ret;
}

void prepare_state(GState stateID) {
    if(nextStateID() != GState::exit) {
        nextStateID() = stateID;
    }
}

void change_state() {
    if(nextStateID() != GState::null) {
        if(nextStateID() != GState::exit) {
            currentState().reset(nullptr);
        }
        
        switch(nextStateID()) {
            case GState::intro:
            currentState().reset(new StateIntro());
            break;
            
            case GState::moon:
            currentState().reset(new StateMoon());
            break;
            
            default:;
        }
        
        currentStateID() = nextStateID();
        nextStateID() = GState::null;
    }
}