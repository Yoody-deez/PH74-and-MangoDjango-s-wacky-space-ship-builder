#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class Slider : public VisualControl {
private:
    float minVal;
    float currentVal;
    float maxVal;
    float step;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 progressColor;
    bool isHovered;
    bool isDragging;

public:
    Slider(float min, float max, float st, Vector2 bCol, Vector2 bgCol, Vector2 pCol);

    float getValue() const;

    void onEvent(Event e) override;

    void render() override;
};