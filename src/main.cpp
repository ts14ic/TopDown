#include "engine/DefaultEngine.h"
#include "engine/DefaultInputContext.h"

int main(int, char* []) {
    DefaultEngine{
            std::make_unique<DefaultInputContext>()
    }.runLoop();
}
