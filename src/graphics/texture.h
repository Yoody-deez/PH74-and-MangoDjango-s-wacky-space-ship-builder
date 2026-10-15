#pragma once
#include "resource.h"

class Texture : public Resource {
private:
    unsigned int id;
    int width;
    int height;

public:
    Texture(const std::string& title, unsigned int textureId, int w, int h);

    ~Texture() override;

    void bind() const;

    void unbind() const;

    unsigned int getId() const;
    int getWidth() const;
    int getHeight() const;
};