#pragma once
#include <string>
#include "../system/Event.h"
#include "../graphics/ResourceManager.h"
#include "visualControl.h"

class progressBar : public visualControl {
private:
    float minVal;
    float currentVal;
    float maxVal;
    vector2 borderColor;
    vector2 bgColor;
    vector2 progressColor;

public:
    progressBar(float min, float max, vector2 bCol, vector2 bgCol, vector2 pCol)
        : minVal(min), maxVal(max), currentVal(min), borderColor(bCol), bgColor(bgCol), progressColor(pCol) {}

    void setProgress(float val) {
        if (val < minVal) currentVal = minVal;
        else if (val > maxVal) currentVal = maxVal;
        else currentVal = val;
    }

    void render() override {
    }
};