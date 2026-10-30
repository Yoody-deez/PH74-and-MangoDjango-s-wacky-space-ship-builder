#include "WindowManager.h"

    void WindowManager::addWindow(std::unique_ptr<Window> win) {
        m_windows.push_back(std::move(win));
    }

    Window* WindowManager::getWindow(size_t index) const {
        if (index < m_windows.size()) {
            return m_windows[index].get();
        }
        return nullptr;
    }

    void WindowManager::makeCurrent(size_t index) {
        if (index < m_windows.size()) {
            SDL_GLContext context = ContextGL::getInstance().getGLContext();
            m_windows[index]->makeCurrent(context);
        }
    }

    void WindowManager::swapBuffersAll() {
        for (auto& win : m_windows) {
            win->swapBuffers();
        }
    }
