#include "engine/DefaultEngine.h"
#include "engine/DefaultInputContext.h"
#include "random/Mt19937Random.h"
#include "engine/DefaultRenderContext.h"

int main(int, char* []) {
    Assets assets;
    DefaultEngine{
            assets,
            std::make_unique<DefaultRenderContext>(assets, 800, 600),
            std::make_unique<DefaultInputContext>(),
            std::make_unique<Mt19937Random>()
    }.runLoop();
}
