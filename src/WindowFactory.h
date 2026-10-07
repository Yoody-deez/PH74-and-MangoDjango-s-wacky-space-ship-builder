#pragma once

#include "Window.h"
#include <memory>
#include <random>

class WindowFactory {
public:
    struct WindowSet {
        std::unique_ptr<Window> at2;
    };

    static WindowSet createWindows() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(300, 400);
        int gSize = distrib(gen);

        SDL_DisplayID primaryDisplay = SDL_GetPrimaryDisplay();
        SDL_Rect displayBounds;
        SDL_GetDisplayBounds(primaryDisplay, &displayBounds);

        int gX = displayBounds.x + (displayBounds.w - gSize) / 2;
        int gY = displayBounds.y + (displayBounds.h - gSize) / 2;

        WindowSet set;
        set.at2 = std::make_unique<Window>("Atelier 2", gX, gY, gSize);

        return set;
    }
};