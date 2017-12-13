#include "engine/DefaultEngine.h"
#include "engine/DefaultInputContext.h"
#include "random/Mt19937Random.h"

int main(int, char* []) {
    DefaultEngine{
            std::make_unique<DefaultInputContext>(),
            std::make_unique<Mt19937Random>()
    }.runLoop();
}
