#include "Graphic.h"

Graphic::~Graphic() = default;

Graphic::FailedToLoadTextureException::FailedToLoadTextureException(const char* message)
        : runtime_error(message) {
}
