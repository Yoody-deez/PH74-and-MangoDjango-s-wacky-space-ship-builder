#pragma once
#include <cstring>
#include <SDL3/SDL.h>
#include <glad/gl.h>
#include "resource.h"

using namespace std;

class Texture : public Resource {
private:
    unsigned int id;
    int width;
    int height;

public:
    Texture(const string& path, bool pixelArt = false);

    Texture(unsigned int existingId, int w, int h);

    ~Texture() override;

    void bind() const;
    void unbind() const;

    unsigned int getId() const;
    int getWidth() const;
    int getHeight() const;
};