#pragma once

#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <string>

class Window {
private:
    SDL_Window* m_sdlWindow = nullptr;
    std::string m_title;

public:
    Window(const std::string& title, int x, int y, int size);

    ~Window();

    SDL_Window* getSDLWindow() const;

    void setTitle(const std::string& title);

    void makeCurrent(SDL_GLContext context);

    void swapBuffers();
};