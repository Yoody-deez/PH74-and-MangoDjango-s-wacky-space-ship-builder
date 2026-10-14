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

    ~Texture() override {}

    void bind() const {}

    void unbind() const {}

    unsigned int getId() const {}
    int getWidth() const {}
    int getHeight() const {}
};