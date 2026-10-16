#pragma once
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include <glad/gl.h>
#include "resource.h"

class texture : public resource {
private:
    unsigned int id;
    int width;
    int height;

public:
    texture(const std::string& path, bool pixelArt = false) : resource(path), id(0), width(0), height(0) {
        SDL_Surface* surface = SDL_LoadSurface(path.c_str());
        if (!surface) {
            std::cerr << "Erreur de chargement d'image (" << path << "): " << SDL_GetError() << std::endl;
            return;
        }

        SDL_Surface* formattedSurface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        SDL_DestroySurface(surface);  

        if (!formattedSurface) {
            std::cerr << "Erreur lors de la conversion de la surface (" << path << "): " << SDL_GetError() << std::endl;
            return;
        }

        width = formattedSurface->w;
        height = formattedSurface->h;

        int pitch = formattedSurface->pitch; 
        void* pixels = formattedSurface->pixels;
        
        char* tempRow = new char[pitch];
        char* row1 = (char*)pixels;
        char* row2 = (char*)pixels + (height - 1) * pitch;

        for (int i = 0; i < height / 2; ++i) {
            memcpy(tempRow, row1, pitch);
            memcpy(row1, row2, pitch);
            memcpy(row2, tempRow, pitch);

            row1 += pitch;
            row2 -= pitch;
        }
        delete[] tempRow;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        GLint filter = pixelArt ? GL_NEAREST : GL_LINEAR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);

        SDL_DestroySurface(formattedSurface);
    }

    texture(unsigned int existingId, int w, int h) 
        : resource("glyph"), id(existingId), width(w), height(h) {}

    ~texture() override {
        if (id != 0) {
            glDeleteTextures(1, &id);
        }
    }

    void bind() const { glBindTexture(GL_TEXTURE_2D, id); }
    void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

    unsigned int getId() const { return id; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};