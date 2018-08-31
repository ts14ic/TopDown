//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../ContextInjector.h"

class SdlContextInjector : public ContextInjector {
public:
    void inject(Engine& engine, int screenWidth, int screenHeight) override;
};
