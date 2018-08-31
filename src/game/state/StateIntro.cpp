#include "StateIntro.h"

StateIntro::StateIntro(Game& engine)
        : _engine{engine},
          _background_tex_id{"intro_background"} {
    engine.get_resources().load_texture(_background_tex_id, "assets/gfx/intro_bg.png");
}

void StateIntro::handle_window_event(const WindowEvent &event) {
}

void StateIntro::handle_mouse_event(const MouseEvent &event) {
}

void StateIntro::handle_key_event(const KeyboardEvent &event) {
    if(event.get_type() == KeyboardEvent::Type::KeyDown) {
        switch(event.get_key()) {
            case 'q': {
                _engine.request_state_change(StateId::exit);
                break;
            }

            case KEY_ESCAPE:
            case KEY_ENTER: {
                _engine.request_state_change(StateId::moon);
                break;
            }

            default: {
                break;
            }
        }
    }
}

void StateIntro::handle_logic() {}

void StateIntro::handle_render(float predictionRatio) {
    auto& render = _engine.get_graphic_context();

    Texture& background = _engine.get_resources().get_texture(_background_tex_id);
    render.render(background, 0, 0);

    render.refresh_screen();
}
