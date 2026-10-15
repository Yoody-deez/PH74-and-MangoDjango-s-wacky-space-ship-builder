#include "texture.h"

using namespace std;

Texture::Texture(const string& title, unsigned int textureId, int w, int h)
: Resource(title), id(textureId), width(w), height(h) {}

Texture::~Texture() {
// Plus tard : glDeleteTextures(1, &id);
}

void Texture::bind() const {
// Plus tard : glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
// Plus tard : glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getId() const { return id; }
int Texture::getWidth() const { return width; }
int Texture::getHeight() const { return height; }