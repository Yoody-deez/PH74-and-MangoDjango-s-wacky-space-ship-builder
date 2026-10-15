#include "resource.h"
#include "texture.h"
#include "font.h"

Font::Font(const string& title) : Resource(title), ftFace(nullptr) {}

Font::~Font() {
		// Plus tard : nettoyage de la police FreeType
}

Texture* Font::generateGlyphTexture(char c) {
		// Logique FreeType à venir
		return nullptr;
}