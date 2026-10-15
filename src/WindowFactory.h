#pragma once

#include "Window.h"
#include <memory>
#include <random>

class WindowFactory {
public:
    struct WindowSet {
        std::unique_ptr<Window> at2;
    };

    static WindowSet createWindows();
};