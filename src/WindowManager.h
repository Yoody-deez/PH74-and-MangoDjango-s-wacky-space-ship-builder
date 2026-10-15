#pragma once

#include "Window.h"
#include "ContextGL.h"
#include <vector>
#include <memory>

using namespace std;

class WindowManager {
private:
    vector<unique_ptr<Window>> m_windows;

public:
    void addWindow(unique_ptr<Window> win);

    Window* getWindow(size_t index = 0) const;

    void makeCurrent(size_t index = 0);

    void swapBuffersAll();
};