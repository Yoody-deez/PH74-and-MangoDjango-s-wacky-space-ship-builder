#pragma once
#include <string>

class Texture;

class font {
private:
    void* ftFace; 

public:
    font() : ftFace(nullptr) {}
    
    virtual ~font() {
        
    }

    Texture* generateGlyphTexture(char c) {
        return nullptr;
    }
};