#include "StateIntro.h"
#include "../engine/Engine.h"
#include "../event/InputContext.h"
#include "../engine/GraphicContext.h"
#include "../resources/Resources.h"
#include "../resources/Texture.h"
#include "../event/KeyboardEvent.h"

StateIntro::StateIntro(Engine& engine)
        : mEngine{engine},
          mBackgroundTexId{"intro_background"} {
    engine.getResources().loadTexture(mBackgroundTexId, "assets/gfx/intro_bg.png");
}

void StateIntro::handleWindowEvent(const WindowEvent& event) {
}

void StateIntro::handleMouseEvent(const MouseEvent& event) {
}

void StateIntro::handleKeyEvent(const KeyboardEvent& event) {
    if(event.getType() == KeyboardEvent::Type::KeyDown) {
        switch(event.getKey()) {
            case 'q': {
                mEngine.requestStateChange(GState::exit);
                break;
            }

            case '\033':
            case '\r': {
                mEngine.requestStateChange(GState::moon);
                break;
            }

            default: {
                break;
            }
        }
    }
}

void StateIntro::handleLogic() {}

void StateIntro::handleRender() {
    auto& render = mEngine.getGraphicContext();

    Texture& background = mEngine.getResources().getTexture(mBackgroundTexId);
    render.render(background, 0, 0);

    render.refreshScreen();
}
