#define STB_TRUETYPE_IMPLEMENTATION
#include "font.h"
#include <fstream>
#include <iostream>



Font::Font(const string& path) : Resource(path), ttfBuffer(nullptr), atlasTextureID(0) {
  atlasWidth = 512; // Divergence
	atlasHeight = 512; // Divergence
	ifstream file(path, ios::binary | ios::ate);
		if (!file.is_open()) {
				cout << "Erreur : Impossible d'ouvrir le fichier de police -> " << path << endl;
				return;
		}

		streamsize size = file.tellg();
		file.seekg(0, ios::beg);

		ttfBuffer = new unsigned char[size];
		if (!file.read((char*)ttfBuffer, size)) {
				cout << "Erreur : Impossible de lire le fichier de police -> " << path << endl;
				delete[] ttfBuffer;
				ttfBuffer = nullptr;
				return;
		}

		if (!stbtt_InitFont(&fontInfo, ttfBuffer, stbtt_GetFontOffsetForIndex(ttfBuffer, 0))) {
				cout << "Erreur : Échec de l'initialisation stb_truetype -> " << path << endl;
				delete[] ttfBuffer;
				ttfBuffer = nullptr;
				return;
		}

		unsigned char* bitmap = new unsigned char[atlasWidth * atlasHeight];
		// Taille de la police fixée à 32 pixels de haut
		stbtt_BakeFontBitmap(ttfBuffer, 0, 32.0f, bitmap, atlasWidth, atlasHeight, 32, 96, cdata);

		glGenTextures(1, &atlasTextureID);
		glBindTexture(GL_TEXTURE_2D, atlasTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlasWidth, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] bitmap;
		cout << "Police TrueType chargée et convertie en atlas : " << path << endl;
}

Font::~Font() {
		if (ttfBuffer) delete[] ttfBuffer;
		if (atlasTextureID != 0) glDeleteTextures(1, &atlasTextureID);
}

void Font::bindAtlas() const {
		glBindTexture(GL_TEXTURE_2D, atlasTextureID);
}

void Font::unbindAtlas() const {
		glBindTexture(GL_TEXTURE_2D, 0);
}

const stbtt_bakedchar* Font::getBakedChars() const {
		return cdata;
}

bool Font::isLoaded() const {
		return ttfBuffer != nullptr;
}