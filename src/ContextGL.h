#pragma once
#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <iostream>


class ContextGL {
private:
    SDL_GLContext m_context = nullptr;

    ContextGL() = default;

public:
    ~ContextGL() {
        if (m_context) {
            SDL_GL_DestroyContext(m_context);
        }
    }

    ContextGL(const ContextGL&) = delete;
    ContextGL& operator=(const ContextGL&) = delete;

    static ContextGL& getInstance() {
        static ContextGL instance;
        return instance;
    }

    bool init(SDL_Window* masterWindow) {
        m_context = SDL_GL_CreateContext(masterWindow);
        if (!m_context) {
            std::cerr << "Erreur de création du contexte GL : " << SDL_GetError() << std::endl;
            return false;
        }

        if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
            std::cerr << "Échec de l'initialisation de GLAD" << std::endl;
            return false;
        }

        return true;
    }

    SDL_GLContext getGLContext() const { return m_context; }
};