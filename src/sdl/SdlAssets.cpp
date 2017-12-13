//
// Created by ts14ic on 12/13/17.
//

#include "SdlAssets.h"


Texture& SdlAssets::texture(std::string const& name) {
    return mNameToTexture[name];
}

Music& SdlAssets::music(std::string const& name) {
    return mNameToMusic[name];
}

Sound& SdlAssets::sound(std::string const& name) {
    return mNameToSound[name];
}
