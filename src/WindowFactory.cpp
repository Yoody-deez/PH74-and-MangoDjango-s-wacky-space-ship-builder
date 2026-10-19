#include "WindowFactory.h"

WindowFactory::WindowSet WindowFactory::createWindows() {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> distrib(300, 400);
		int gSize = distrib(gen);

		SDL_DisplayID primaryDisplay = SDL_GetPrimaryDisplay();
		SDL_Rect displayBounds;
		SDL_GetDisplayBounds(primaryDisplay, &displayBounds);

		int gX = displayBounds.x + (displayBounds.w - gSize) / 2;
		int gY = displayBounds.y + (displayBounds.h - gSize) / 2;

		WindowSet set;
		set.at2 = make_unique<Window>("Atelier 2", gX, gY, gSize);

		return set;
}