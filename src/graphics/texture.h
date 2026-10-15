#pragma once
#include "resource.h"

using namespace std;

class Texture : public Resource {
private:
    unsigned int id;
    int width;
    int height;

public:
    Texture(const string& title, unsigned int textureId, int w, int h);

    ~Texture() override;

    void bind() const;

    void unbind() const;

    unsigned int getId() const;
    int getWidth() const;
    int getHeight() const;
};