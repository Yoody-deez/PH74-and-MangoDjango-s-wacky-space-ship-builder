#pragma once
#include "resource.h"
#include "texture.h"

class Font : public Resource {
private:
    void* ftFace;

public:
    Font(const std::string& title);

    ~Font() override;

    Texture* generateGlyphTexture(char c);
};