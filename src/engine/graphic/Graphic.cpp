#include "Graphic.h"

Graphic::~Graphic() = default;

Graphic::FailedToLoadTextureException::FailedToLoadTextureException(cstring message)
        : runtime_error(message) {
}
