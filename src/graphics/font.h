#pragma once
#include <string>
#include "resource.h"
#include "texture.h"

using namespace std;

class Font : public Resource {
private:
    Texture* atlasTexture;

public:
    Font(const string& path);

    ~Font() override;

    Texture* getAtlas() const;
};