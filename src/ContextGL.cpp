#include "ContextGL.h"
#include <glad/gl.h>
#include <iostream>

ContextGL::ContextGL() = default;

ContextGL::~ContextGL() {
		if (m_context) {
				SDL_GL_DestroyContext(m_context);
		}
}

ContextGL& ContextGL::getInstance() {
		static ContextGL instance;
		return instance;
}

bool ContextGL::init(SDL_Window* masterWindow) {
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

SDL_GLContext ContextGL::getGLContext() const { return m_context; }
