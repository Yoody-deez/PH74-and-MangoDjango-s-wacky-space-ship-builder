#pragma once

#include "Window.h"
#include "ContextGL.h"
#include <vector>
#include <memory>

class WindowManager {
private:
    std::vector<std::unique_ptr<Window>> m_windows;

public:
    void addWindow(std::unique_ptr<Window> win) {}

    Window* getWindow(size_t index = 0) const {}

    void makeCurrent(size_t index = 0) {}

    void swapBuffersAll() {}
};