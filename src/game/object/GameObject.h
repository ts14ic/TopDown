#pragma once

#include <game/mixins/HasTransform.h>
#include <game/mixins/HasSpeed.h>
#include <engine/graphic/Graphic.h>
#include <iosfwd>

class GameObject : public HasTransform, public HasSpeed {
public:
    virtual std::string get_tex_name() const = 0;
protected:
    void default_move();

    void default_render(Graphic& graphic, float frames_count);
};

bool objects_collide(GameObject& a, GameObject& b);
