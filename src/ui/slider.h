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
<<<<<<< HEAD
    slider(float min, float max, float st, Vector2 pos, Vector2 s,
           Vector2 bCol = Vector2(0,0), Vector2 bgCol = Vector2(0.2f,0.2f), Vector2 pCol = Vector2(0.5f,0.5f))
        : minVal(min), maxVal(max), currentVal(min), step(st), 
          borderColor(bCol), bgColor(bgCol), progressColor(pCol), 
          isHovered(false), isDragging(false) {
        position = pos;
        size = s;
    }
=======
    Slider(float min, float max, float st, Vector2 bCol, Vector2 bgCol, Vector2 pCol);
>>>>>>> yannick-seperation

    float getValue() const;

    void onEvent(Event e) override;

    void render() override;
};