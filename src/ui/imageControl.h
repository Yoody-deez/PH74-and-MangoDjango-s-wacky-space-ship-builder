#pragma once
#include <string>
#include "../system/event.h"
#include "VisualControl.h"
#include "texture.h"

class imageControl : public visualControl {
private:
    Texture* texture;
    bool keepAspect;

public:
    imageControl(Texture* tex, bool aspect = true) : texture(tex), keepAspect(aspect) {}

    void render() override {
    }
};