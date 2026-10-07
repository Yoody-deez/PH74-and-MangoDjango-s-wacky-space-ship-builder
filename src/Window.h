#pragma once

#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <string>

class Window {
private:
    SDL_Window* m_sdlWindow = nullptr;
    std::string m_title;

public:
    Window(const std::string& title, int x, int y, int size)
        : m_title(title)
    {
        m_sdlWindow = SDL_CreateWindow(m_title.c_str(), size, size, SDL_WINDOW_OPENGL);
        if (m_sdlWindow && x >= 0 && y >= 0) {
            SDL_SetWindowPosition(m_sdlWindow, x, y);
        }
    }

    ~Window() {
        if (m_sdlWindow) {
            SDL_DestroyWindow(m_sdlWindow);
        }
    }

    SDL_Window* getSDLWindow() const {
        return m_sdlWindow;
    }

    void setTitle(const std::string& title) {
        m_title = title;
        if (m_sdlWindow) {
            SDL_SetWindowTitle(m_sdlWindow, m_title.c_str());
        }
    }

    void makeCurrent(SDL_GLContext context) {
        SDL_GL_MakeCurrent(m_sdlWindow, context);
    }

    void swapBuffers() {
        SDL_GL_SwapWindow(m_sdlWindow);
    }
};