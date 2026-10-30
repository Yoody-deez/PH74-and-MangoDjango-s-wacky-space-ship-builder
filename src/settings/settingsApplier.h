#pragma once

#include "../core/configManager.h"
#include <SDL3/SDL.h>

class SettingsApplier {
public:
    static void applySettings(SDL_Window* sdlWin);
};