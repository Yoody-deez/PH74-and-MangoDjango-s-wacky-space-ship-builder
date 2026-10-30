#pragma once
#include <string>
#include "../system/event.h"
#include "visualControl.h"
#include "../graphics/texture.h"
#include "../shaders/shader.h"

class ImageControl : public VisualControl {
private:
    Texture* myTexture;
    bool keepAspect;
    unsigned int VAO, VBO;

public:
    ImageControl(Texture* tex, bool aspect = true) ;

    ~ImageControl() override;

    void render() override;
};