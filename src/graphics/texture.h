#pragma once
#include <string>
#include "resource.h"

class Texture : public Resource {
private:
    unsigned int id;
    int width;
    int height;

public:
    Texture(const std::string& path, bool pixelArt = false);

    Texture(unsigned int existingId, int w, int h);

    ~Texture() override;

    void bind() const;
    void unbind() const;

    unsigned int getId() const;
    int getWidth() const;
    int getHeight() const;
};