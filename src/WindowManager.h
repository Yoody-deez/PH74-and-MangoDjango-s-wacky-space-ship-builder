#pragma once

#include "Window.h"
#include "ContextGL.h"
#include <vector>
#include <memory>

class WindowManager {
private:
    std::vector<std::unique_ptr<Window>> m_windows;

public:
    void addWindow(std::unique_ptr<Window> win) {
        m_windows.push_back(std::move(win));
    }

    Window* getWindow(size_t index = 0) const {
        if (index < m_windows.size()) {
            return m_windows[index].get();
        }
        return nullptr;
    }

    void makeCurrent(size_t index = 0) {
        if (index < m_windows.size()) {
            SDL_GLContext context = ContextGL::getInstance().getGLContext();
            m_windows[index]->makeCurrent(context);
        }
    }

    void swapBuffersAll() {
        for (auto& win : m_windows) {
            win->swapBuffers();
        }
    }
};