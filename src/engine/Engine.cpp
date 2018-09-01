#include "Engine.h"

Engine::~Engine() = default;

Engine::FailedEngineInitException::FailedEngineInitException(const char* message)
        : runtime_error(message) {}
