#pragma once
#include <string>
#include <glad/gl.h>
#include "../system/event.h"
#include "VisualControl.h"
#include "../graphics/texture.h"
#include "../shaders/shader.h"

class ImageControl : public VisualControl {
private:
    Texture* myTexture;
    bool keepAspect;
    unsigned int VAO, VBO;

public:
    ImageControl(Texture* tex, bool aspect = true);

    void render() override;
};