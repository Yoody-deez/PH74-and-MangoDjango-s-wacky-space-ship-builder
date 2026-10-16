#include "font.h"

Font::Font(const string& path) : Resource(path), atlasTexture(nullptr) {
	atlasTexture = new Texture(path, true);
}

Font::~Font() {
		delete atlasTexture;
}

Texture* Font::getAtlas() const {
		return atlasTexture;
}