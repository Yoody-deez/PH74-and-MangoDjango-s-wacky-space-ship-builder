#pragma once
#include <string>
#include "resource.h"
#include "texture.h"

class font : public resource {
private:
    texture* atlasTexture;

public:
    font(const std::string& path) : resource(path), atlasTexture(nullptr) {
        atlasTexture = new texture(path, true);
    }

    ~font() override {
        delete atlasTexture;
    }

    texture* getAtlas() const {
        return atlasTexture;
    }
};