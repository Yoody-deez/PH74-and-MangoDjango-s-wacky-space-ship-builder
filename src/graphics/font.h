#pragma once
#include "resource.h"
#include "texture.h"

class font : public resource {
private:
    void* ftFace;

public:
    font(const std::string& title) : resource(title), ftFace(nullptr) {}

    ~font() override {
        // Plus tard : nettoyage de la police FreeType
    }

    Texture* generateGlyphTexture(char c) {
        // Logique FreeType à venir
        return nullptr;
    }
};