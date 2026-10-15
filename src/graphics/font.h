#pragma once
#include "resource.h"
#include "texture.h"

using namespace std;

class Font : public Resource {
private:
    void* ftFace;

public:
    Font(const string& title);

    ~Font() override;

    Texture* generateGlyphTexture(char c);
};