#include "settingsApplier.h"
#include <glad/gl.h>
#include <iostream>

void SettingsApplier::applySettings(SDL_Window* sdlWin) {
		auto& config = ConfigManager::getInstance();

		int vsyncVal = config.isVsync() ? 1 : 0;
		if (!SDL_GL_SetSwapInterval(vsyncVal)) {
				std::cerr << "Erreur VSync : " << SDL_GetError() << std::endl;
		} else {
				std::cout << "[APPLIQUER] VSync regle a : " << (config.isVsync() ? "On" : "Off") << std::endl;
		}

		int resIdx = config.getResolutionIndex();
		int w = 800, h = 600;
		if (resIdx == 1) { w = 1280; h = 720; }
		else if (resIdx == 2) { w = 1920; h = 1080; }

		if (config.isFullscreen()) {
				SDL_SetWindowFullscreen(sdlWin, true);
		} else {
				SDL_SetWindowFullscreen(sdlWin, false);
				SDL_SetWindowSize(sdlWin, w, h);
				SDL_SetWindowPosition(sdlWin, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		}

		std::cout << "[APPLIQUER] Resolution appliquee : " << w << "x" << h << std::endl;

		int pixelWidth, pixelHeight;
		SDL_GetWindowSizeInPixels(sdlWin, &pixelWidth, &pixelHeight);
		glViewport(0, 0, pixelWidth, pixelHeight);
}
