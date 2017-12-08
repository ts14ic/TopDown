//
// Created by ts14ic on 12/8/17.
//

#include "Assets.h"

Texture& Assets::texture(std::string const& name) {
    return mNameToTexture[name];
}

Music& Assets::music(std::string const& name) {
    return mNameToMusic[name];
}

Sound& Assets::sound(std::string const& name) {
    return mNameToSound[name];
}
