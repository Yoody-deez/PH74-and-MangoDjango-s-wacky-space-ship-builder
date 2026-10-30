#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <glad/gl.h>
#include "resource.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include "stb_truetype.h"

using namespace std;

class Font : public Resource {
private:
    unsigned char* ttfBuffer;
    stbtt_fontinfo fontInfo;
    stbtt_bakedchar cdata[96]; 
    unsigned int atlasTextureID;
    int atlasWidth = 512;
    int atlasHeight = 512;

public:
    Font(const std::string& path) : Resource(path), ttfBuffer(nullptr), atlasTextureID(0) {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            std::cout << "Erreur : Impossible d'ouvrir le fichier de police -> " << path << std::endl;
            return;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        ttfBuffer = new unsigned char[size];
        if (!file.read((char*)ttfBuffer, size)) {
            std::cout << "Erreur : Impossible de lire le fichier de police -> " << path << std::endl;
            delete[] ttfBuffer;
            ttfBuffer = nullptr;
            return;
        }

        if (!stbtt_InitFont(&fontInfo, ttfBuffer, stbtt_GetFontOffsetForIndex(ttfBuffer, 0))) {
            std::cout << "Erreur : Échec de l'initialisation stb_truetype -> " << path << std::endl;
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
        std::cout << "Police TrueType chargée et convertie en atlas : " << path << std::endl;
    }

    ~Font() override {
        if (ttfBuffer) delete[] ttfBuffer;
        if (atlasTextureID != 0) glDeleteTextures(1, &atlasTextureID);
    }

    void bindAtlas() const {
        glBindTexture(GL_TEXTURE_2D, atlasTextureID);
    }

    void unbindAtlas() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    const stbtt_bakedchar* getBakedChars() const {
        return cdata;
    }

    bool isLoaded() const {
        return ttfBuffer != nullptr;
    }
};