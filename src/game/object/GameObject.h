#pragma once

#include <game/mixins/HasTransform.h>
#include <game/mixins/HasSpeed.h>
#include <game/mixins/HasTexture.h>
#include <engine/graphic/Graphic.h>

class GameObject : public HasTransform, public HasSpeed, public HasTexture {
protected:
    void default_move();

    void default_render(Graphic& graphic, float frames_count);
};

bool objects_collide(GameObject& a, GameObject& b);
