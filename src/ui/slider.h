#pragma once
#include <string>
#include "../system/event.h"
#include "visualControl.h"
#include "label.h"

class Slider : public VisualControl {
private:
    float minVal;
    float currentVal;
    float maxVal;
    float step;
    bool isHovered;
    bool isDragging;
    unsigned int VAO, VBO;
    unsigned int trackTextureID;
    Label valueLabel;

    unsigned int createSolidTexture(unsigned int colorHex);

    void initQuad();

public:
    Slider(float min, float max, float st, Vector2 pos, Vector2 s, Font* f);

    ~Slider() override;

    float getValue() const;

    void updateLabelPositionAndText();

    void onEvent(Event e) override;

    void render() override;
};