#pragma once
#include <string>
#include "../system/event.h"
#include "VisualControl.h"
#include "texture.h"

class ImageControl : public VisualControl {
private:
    Texture* texture;
    bool keepAspect;

public:
    ImageControl(Texture* tex, bool aspect = true);

    void render() override;
};