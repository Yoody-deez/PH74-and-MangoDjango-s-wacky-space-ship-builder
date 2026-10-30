#pragma once
#include <SDL3/SDL.h>


class ContextGL {
private:
    SDL_GLContext m_context = nullptr;

    ContextGL();

public:
    ~ContextGL();

    ContextGL(const ContextGL&) = delete;
    ContextGL& operator=(const ContextGL&) = delete;

    static ContextGL& getInstance();

    bool init(SDL_Window* masterWindow);

    SDL_GLContext getGLContext() const;
};