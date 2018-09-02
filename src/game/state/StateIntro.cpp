#include "StateIntro.h"

StateIntro::StateIntro(Game& game)
        : _game{game},
          _background_tex_id{"intro_background"} {
    _game.get_engine().get_graphic().load_texture(_background_tex_id, "assets/gfx/intro_bg.png");
}

void StateIntro::handle_window_event(const WindowEvent &event) {
}

void StateIntro::handle_mouse_event(const MouseScrollEvent &event) {
}

void StateIntro::handle_mouse_event(const MousePointEvent& event) {
}

void StateIntro::handle_key_event(const KeyboardEvent &event) {
    if(event.get_type() == KeyboardEvent::Type::KEY_DOWN) {
        switch(event.get_key()) {
            case 'q': {
                _game.request_state_change(StateId::EXIT);
                break;
            }

            case KEY_ESCAPE:
            case KEY_ENTER: {
                _game.request_state_change(StateId::MOON);
                break;
            }

            default: {
                break;
            }
        }
    }
}

void StateIntro::handle_logic() {}

void StateIntro::handle_render(float frames_count) {
    auto& graphic = _game.get_engine().get_graphic();

    graphic.render_texture(_background_tex_id, make_point(0, 0));

    graphic.refresh_screen();
}
