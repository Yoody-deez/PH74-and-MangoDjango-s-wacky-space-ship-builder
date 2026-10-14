#include "Window.h"

Window::Window(const std::string& title, int x, int y, int size)
		: m_title(title)
{
		m_sdlWindow = SDL_CreateWindow(m_title.c_str(), size, size, SDL_WINDOW_OPENGL);
		if (m_sdlWindow && x >= 0 && y >= 0) {
				SDL_SetWindowPosition(m_sdlWindow, x, y);
		}
}

Window::~Window() {
		if (m_sdlWindow) {
				SDL_DestroyWindow(m_sdlWindow);
		}
}

SDL_Window* Window::getSDLWindow() const {
		return m_sdlWindow;
}

void Window::setTitle(const std::string& title) {
		m_title = title;
		if (m_sdlWindow) {
				SDL_SetWindowTitle(m_sdlWindow, m_title.c_str());
		}
}

void Window::makeCurrent(SDL_GLContext context) {
		SDL_GL_MakeCurrent(m_sdlWindow, context);
}

void Window::swapBuffers() {
		SDL_GL_SwapWindow(m_sdlWindow);
}