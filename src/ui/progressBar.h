#pragma once
#include <string>
#include "../system/event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class progressBar : public visualControl {
private:
    float minVal;
    float currentVal;
    float maxVal;
    Vector2 borderColor;
    Vector2 bgColor;
    Vector2 progressColor;

public:
    progressBar(float min, float max, Vector2 bCol, Vector2 bgCol, Vector2 pCol)
        : minVal(min), maxVal(max), currentVal(min), borderColor(bCol), bgColor(bgCol), progressColor(pCol) {}

    void setProgress(float val) {
        if (val < minVal) currentVal = minVal;
        else if (val > maxVal) currentVal = maxVal;
        else currentVal = val;
    }

    void render() override {
    }
};