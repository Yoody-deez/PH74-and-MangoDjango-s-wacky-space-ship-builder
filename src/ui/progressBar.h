#pragma once
#include <string>
#include <glad/gl.h>
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
    unsigned int VAO, VBO;

    void initQuad();

public:
    ProgressBar(float min, float max, Vector2 pos, Vector2 s, 
                Vector2 bCol = Vector2(0,0), Vector2 bgCol = Vector2(0.2f,0.2f), Vector2 pCol = Vector2(0.5f,0.5f));

    ~ProgressBar() override;

    void setProgress(float val);

    float getProgress() const;

    void render() override;
};