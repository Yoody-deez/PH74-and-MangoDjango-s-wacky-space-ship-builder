#pragma once
#include <string>
#include "../system/Event.h"
#include "VisualControl.h"

class Texture;

class imageControl : public visualControl {
private:
    Texture* texture;
    bool keepAspect;

public:
    imageControl(Texture* tex, bool aspect = true) : texture(tex), keepAspect(aspect) {}

    void render() override {
    }
};