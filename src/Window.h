#pragma once

#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <string>

using namespace std;

class Window {
private:
    SDL_Window* m_sdlWindow = nullptr;
    string m_title;

public:
    Window(const string& title, int x, int y, int size);

    ~Window();

    SDL_Window* getSDLWindow() const;

    void setTitle(const string& title);

    void makeCurrent(SDL_GLContext context);

    void swapBuffers();
};