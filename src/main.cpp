#include "engine/DefaultEngine.h"

int main(int, char* []) {
    DefaultEngine{
            std::make_unique<DefaultInputContext>()
    }.runLoop();
}
