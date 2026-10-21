#pragma once
#include <string>
#include <glad/gl.h>
#include "resource.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

using namespace std;

class Font : public Resource {
private:
    unsigned char* ttfBuffer;
    stbtt_fontinfo fontInfo;
    stbtt_bakedchar cdata[96];
    unsigned int atlasTextureID;
    int atlasWidth;
    int atlasHeight;
public:
    Font(const std::string& path);

    ~Font() override;

    void bindAtlas() const;

    void unbindAtlas() const;

    const stbtt_bakedchar* getBakedChars() const;

    bool isLoaded() const;
};