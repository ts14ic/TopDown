#include "Engine.h"

Engine::~Engine() = default;

Engine::FailedEngineInitException::FailedEngineInitException(cstring message)
        : runtime_error(message) {}
