#pragma once
#include "resource.h"

class Texture : public resource {
private:
    unsigned int id;
    int width;
    int height;

public:
    Texture(const std::string& title, unsigned int textureId, int w, int h)
        : resource(title), id(textureId), width(w), height(h) {}

    ~Texture() override {
        // Plus tard : glDeleteTextures(1, &id);
    }

    void bind() const {
        // Plus tard : glBindTexture(GL_TEXTURE_2D, id);
    }

    void unbind() const {
        // Plus tard : glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int getId() const { return id; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};