#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class ProgressBar : public VisualControl {
private:
    float minVal;
    float currentVal;
    float maxVal;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 progressColor;

public:
    ProgressBar(float min, float max, Vector2 bCol, Vector2 bgCol, Vector2 pCol);

    void setProgress(float val);

    void render() override;
};