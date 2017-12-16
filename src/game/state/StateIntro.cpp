#include "StateIntro.h"
#include "../../engine/Engine.h"
#include "../../engine/input/InputContext.h"
#include "../../engine/GraphicContext.h"
#include "../../resources/Resources.h"
#include "../../resources/Texture.h"
#include "../../engine/input/KeyboardEvent.h"

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

            case KEY_ESCAPE:
            case KEY_ENTER: {
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

void StateIntro::handleRender(float predictionRatio) {
    auto& render = mEngine.getGraphicContext();

    Texture& background = mEngine.getResources().getTexture(mBackgroundTexId);
    render.render(background, 0, 0);

    render.refreshScreen();
}
