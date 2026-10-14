#include "resource.h"
#include "texture.h"
#include "font.h"

font::font(const std::string& title) : resource(title), ftFace(nullptr) {}

font::~font() {
		// Plus tard : nettoyage de la police FreeType
}

Texture* font::generateGlyphTexture(char c) {
		// Logique FreeType à venir
		return nullptr;
}