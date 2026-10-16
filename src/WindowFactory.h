#pragma once

#include "Window.h"
#include <memory>
#include <random>

using namespace std;

class WindowFactory {
public:
    struct WindowSet {
        unique_ptr<Window> at2;
    };

    static WindowSet createWindows();
};