#pragma once
#include <string>
#include <glad/gl.h>
#include "resource.h"
#include "stb_truetype.h"

class Font : public Resource {
private:
    static constexpr int FIRST_CHAR = 32; // Premier caractère ASCII à inclure dans l'atlas de caractères (espace)
    static constexpr int NUM_CHARS = 224; // Nombre total de caractères à inclure dans l'atlas de caractères (de l'espace à 255)
    static constexpr int ATLAS_WIDTH = 1024; // Largeur de l'atlas de caractères
    static constexpr int ATLAS_HEIGHT = 1024; // Hauteur de l'atlas de caractères
    
    unsigned char* ttfBuffer;
    stbtt_fontinfo fontInfo;
    stbtt_bakedchar cdata[NUM_CHARS];
    unsigned int atlasTextureID;


public:
    Font(const std::string& path);

    ~Font() override ;

    void bindAtlas() const;

    void unbindAtlas() const;

    const stbtt_bakedchar* getBakedChars() const;

    bool isLoaded() const;
};