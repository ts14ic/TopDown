#include "engine/DefaultEngine.h"
#include "engine/DefaultInputContext.h"
#include "random/Mt19937Random.h"
#include "engine/DefaultRenderContext.h"
#include "assets/SdlAssets.h"

int main(int, char* []) {
    DefaultEngine{
            std::make_unique<SdlAssets>(),
            std::make_unique<DefaultRenderContext>(800, 600),
            std::make_unique<DefaultInputContext>(),
            std::make_unique<Mt19937Random>()
    }.runLoop();
}
